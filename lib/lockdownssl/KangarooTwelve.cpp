#include <deque>
#include <thread>
#include <functional>

#include "lockdownssl/KangarooTwelve.h"

using namespace LockdownSSL;

#define CHUNKSIZE 8192

struct Encoded
{
    byte encodedlen[9] = {0,0,0,0,0,0,0,0,0};
    byte len;
};

static byte AccessByte(word64 Val, byte i)
{
    word64 mask = 0xFF00000000000000;
    return ( Val & ( mask >> 8 * i ) ) >> 8 * (7 - i);
}

static Encoded RightEncode(word64 Val)
{
    Encoded enc;

    if(!Val) { enc.len = 1; return enc; }

    byte i = 0;
    for(; i < 8; i++)
    {
        if(byte tmp = AccessByte(Val, i))
        {
            enc.len = 8 - i;
            enc.encodedlen[0] = tmp;
            i++;
            break;
        }
    }

    for(byte c = 1; i < 8; i++, c++)
    {
        enc.encodedlen[c] = AccessByte(Val, i);
    }

    enc.encodedlen[enc.len] = enc.len;
    enc.len++;

    return enc;
}

template<byte Rate, byte IntermDigestSize, byte NumRounds>
void KangarooTwelve<Rate, IntermDigestSize, NumRounds>::Put(const SecureBlock<byte>& Data)
{
    size_t initial = m_Data.Size();
    m_Data.Grow(Data.Size());
    std::memcpy(m_Data.Data() + initial, Data.Data(), Data.Size());
}

static void ChunkIt(byte* Data, size_t DataSize, std::deque<SecureBlock<byte>>& CVQ) 
{
    if(DataSize)
    {
        size_t copyable = DataSize > CHUNKSIZE ? CHUNKSIZE : DataSize;
        CVQ.push_back(SecureBlock<byte>(Data, copyable));

        ChunkIt(Data + copyable, DataSize - copyable, CVQ);
    }
}

static void ProcessSerial(std::deque<SecureBlock<byte>>& CVQ, std::function<void(SecureBlock<byte>&)> F, byte* begin)
{
    size_t ind = 0;
    for(size_t i = 0; i < CVQ.size(); i++)
    {
        F(CVQ.at(i));

        for(byte b : CVQ.at(i))
            begin[ind++] = b;
    }
}

static void ProcessParallelHelper(SecureBlock<byte>& Block, std::function<void(SecureBlock<byte>&)> F, byte* begin)
{
    F(Block);
    std::memmove(begin, Block.Data(), Block.Size());
}

static void WaitForThreads(std::deque<std::thread>& threadQ)
{
    for(byte i = 0; i < threadQ.size(); i++)
        threadQ.at(i).join();

    threadQ.clear();
}

static void ProcessParallel(std::deque<SecureBlock<byte>>& CVQ, std::function<void(SecureBlock<byte>&)> F, byte* begin)
{
    byte numThreads = CVQ.size() >= 8 ? 8 : 4;

    std::deque<std::thread> threadQ;

    for(size_t i = 0, t = 0; i < CVQ.size(); i++, t++)
    {
        if(t == numThreads)
        {
            t = 0;
            WaitForThreads(threadQ);
        }

        threadQ.push_back( 
            std::move( 
                std::thread(ProcessParallelHelper, std::ref(CVQ.at(i)), F, begin) 
            ) 
        );

        begin += CHUNKSIZE;
    }

    WaitForThreads(threadQ);
    CVQ.clear();
}

static void AddAuxiliaury(SecureBlock<byte>& m_Data, Encoded& enc)
{
    byte app[] = { 0xC0, 0, 0, 0, 0, 0, 0, 0 };

    for(byte i = 0; i < 8; i++)
        m_Data[CHUNKSIZE + i] = app[i];

    for(size_t a = m_Data.Size() - 2 - enc.len, i = 0; i < enc.len; i++, a++)
        m_Data[a] = enc.encodedlen[i];

    m_Data[m_Data.Size() - 1] = 0xFF;
    m_Data[m_Data.Size() - 2] = 0xFF;
}

template<byte Rate, byte IntermDigestSize, byte NumRounds>
SecureBlock<byte> KangarooTwelve<Rate, IntermDigestSize, NumRounds>::Digest()
{
    size_t initial = m_Data.Size();

    Encoded enc = RightEncode(m_CustomisationString.size());

    m_Data.Grow(m_CustomisationString.size() + enc.len);

    std::memcpy(m_Data.Data() + initial, m_CustomisationString.data(), m_CustomisationString.size());
    std::memcpy(m_Data.Data() + initial + m_CustomisationString.size(), enc.encodedlen, enc.len);

    if(m_Data.Size() <= CHUNKSIZE)
    {
        SetDomain(0x07);
        Keccak_P_1600::SetDigestSize(m_FinalDigestSize);
        Hash(m_Data);
        return m_Data;
    }

    SetDomain(0x0B);
    Keccak_P_1600::SetDigestSize(IntermDigestSize);

    std::deque<SecureBlock<byte>> CVQ;
    ChunkIt(m_Data.Data() + CHUNKSIZE, m_Data.Size() - CHUNKSIZE, CVQ);

    enc = RightEncode(CVQ.size() - 1);

    m_Data.Resize(CHUNKSIZE + 8 + CVQ.size() * IntermDigestSize + enc.len + 2);

   std::function<void(SecureBlock<byte>&)> F = [this](SecureBlock<byte>& Data) { Hash(Data); return; };

    if(CVQ.size() < 4)
    {
        std::thread process(ProcessSerial, std::ref(CVQ), F, m_Data.Data() + CHUNKSIZE + 8);

        AddAuxiliaury(m_Data, enc);

        process.join();
    }
    else
    {
        std::thread process(ProcessParallel, std::ref(CVQ), F, m_Data.Data() + CHUNKSIZE + 8);
        
        AddAuxiliaury(m_Data, enc);

        process.join();
    }

    SetDomain(0x06);
    Keccak_P_1600::SetDigestSize(m_FinalDigestSize);
    Hash(m_Data);

    return m_Data;
}

template class KangarooTwelve<168, 32, 12>;
template class KangarooTwelve<136, 64, 14>;

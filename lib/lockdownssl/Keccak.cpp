#include "lockdownssl/Keccak.h"
#include "misc/BitRotation.h"

using namespace LockdownSSL;

static const unsigned int s_KECCAK_RO_RAW[5][5] =
{
    {0, 1, 190, 28, 91},
    {36, 300, 6, 55, 276},
    {3, 10, 171, 153, 231},
    {105, 45, 15, 21, 136},
    {210, 66, 253, 120, 78},
};

static const word64 s_KECCAK_RC_RAW[24] =
{
    0x0000000000000001, 0x0000000000008082, 0x800000000000808A, 0x8000000080008000, 0x000000000000808B, 0x0000000080000001,
    0x8000000080008081, 0x8000000000008009, 0x000000000000008A, 0x0000000000000088, 0x0000000080008009, 0x000000008000000A,
    0x000000008000808B, 0x800000000000008B, 0x8000000000008089, 0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
    0x000000000000800A, 0x800000008000000A, 0x8000000080008081, 0x8000000000008080, 0x0000000080000001, 0x8000000080008008,
};

template<typename T>
static inline T RoundConstant(byte round)
{
    word64 mask = 0xFFFFFFFFFFFFFFFF;
    return ( s_KECCAK_RC_RAW[round] & ( mask >> 8 * ( sizeof(word64) - sizeof(T) ) ) );
}

template<typename T>
static inline byte RotationOffset(int y, int x)
{
    return s_KECCAK_RO_RAW[y][x] % ( 8 * sizeof(T) );
}

static void Padding(SecureBlock<byte>& data, byte Rate, byte Domain)
{
    size_t initialSize = data.Size();

    byte size_padding = Rate - ( ( initialSize + 1 ) % Rate);

    data.CleanGrow(size_padding + 1);

    data[initialSize] = Domain;

    data[data.Size() - 1] ^= 0x80;
}

#define THETA_PERM_1(i) C[i] = (state[0][i]) ^ (state[1][i]) ^ (state[2][i]) ^ (state[3][i]) ^ (state[4][i]);

#define THETA_PERM_2(i) D[i] = ( C[ ( i + 4 ) % 5 ] ) ^ rotl(C[ ( i + 1 ) % 5 ], 1);

#define THETA_PERM_3_IN(y,x) state[y][x] ^= D[x];
#define THETA_PERM_3(x) \
THETA_PERM_3_IN(0,x) \
THETA_PERM_3_IN(1,x) \
THETA_PERM_3_IN(2,x) \
THETA_PERM_3_IN(3,x) \
THETA_PERM_3_IN(4,x)

#define THETA(state) \
THETA_PERM_1(0)\
THETA_PERM_1(1)\
THETA_PERM_1(2)\
THETA_PERM_1(3)\
THETA_PERM_1(4)\
THETA_PERM_2(0)\
THETA_PERM_2(1)\
THETA_PERM_2(2)\
THETA_PERM_2(3)\
THETA_PERM_2(4)\
THETA_PERM_3(0)\
THETA_PERM_3(1)\
THETA_PERM_3(2)\
THETA_PERM_3(3)\
THETA_PERM_3(4)

#define RHO_PI_IN(y,x) B[(2 * x + 3 * y) % 5][y] = rotl( state[y][x], RotationOffset<T>(y,x) );
#define RHO_PI(x) \
RHO_PI_IN(0,x)\
RHO_PI_IN(1,x)\
RHO_PI_IN(2,x)\
RHO_PI_IN(3,x)\
RHO_PI_IN(4,x)

#define CHI_IN(y,x) state[y][x] = B[y][x] ^ ( ~( B[y][ ( x + 1 ) % 5] ) & ( B[y][ ( x + 2 ) % 5] ) );
#define CHI(x) \
CHI_IN(0,x)\
CHI_IN(1,x)\
CHI_IN(2,x)\
CHI_IN(3,x)\
CHI_IN(4,x)

#define RHO_PI_CHI(state) \
RHO_PI(0)\
RHO_PI(1)\
RHO_PI(2)\
RHO_PI(3)\
RHO_PI(4)\
CHI(0)\
CHI(1)\
CHI(2)\
CHI(3)\
CHI(4)

#define IOTA(state, iteration) state[0][0] ^= RoundConstant<T>(iteration);

template<typename T>
static void Keccak_P(T(&state)[5][5], byte NumRounds)
{
    T C[5];
    T D[5];
    T B[5][5];

    for(byte i = 24 - NumRounds; i < 24; i++)
    {
        THETA(state)
        RHO_PI_CHI(state)
        IOTA(state, i)
    }
}

template<typename T>
static void Squeeze(SecureBlock<byte>& Data, byte Rate, byte NumRounds, size_t DigestSize, T(&state)[5][5])
{
    Data.Resize(DigestSize);

    size_t processed_bytes = 0;

    goto START_EXTRACT;

    do
    {
        Keccak_P(state, NumRounds);

START_EXTRACT:
        byte x = 0, y = 0;

        do
        {
            T tmp = state[y][x++];

            if(x == 5) { x = 0; y++; }

            for(byte i = 0; i < sizeof(T) && ( processed_bytes + 1 ) % ( Rate + 1 ) != 0 && processed_bytes < DigestSize; i++, processed_bytes++)
            {
                word64 mask = 0x00000000000000FF;
                Data[processed_bytes] = (byte) ( ( tmp & (mask << 8 * i) ) >> 8 * i );
            }

        }while( ( processed_bytes + 1) % ( Rate + 1 ) != 0 && processed_bytes < DigestSize);

    } while (processed_bytes < DigestSize);
}



template<typename T>
T StateVal(byte* Data, byte Rate, byte& Processed)
{
    T val = 0;

    for(signed char i = sizeof(T) - 1; i >= 0 && Processed < Rate; i--, Processed++)
    {
        val <<= 8;
        val |= Data[i];
    }

    return val;
}

template<typename T>
static void Sponge(SecureBlock<byte>& Data, byte Rate, byte NumRounds, size_t DigestSize)
{
    T state[5][5] = 
    {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
    };

    size_t num_parts = Data.Size() / Rate;

    for(size_t p = 0; p < num_parts; p++)
    {
        byte x = 0, y = 0, processed = 0;

        while(processed < Rate)
        {
            state[y][x++] ^= StateVal<T>(Data.Data() + processed + p * Rate, Rate, processed);

            if(x == 5) { x = 0; y++; }
        }
        
        Keccak_P(state, NumRounds);
    }

    Squeeze(Data, Rate, NumRounds, DigestSize, state);
}

template<typename T>
void Keccak<T>::Digest(SecureBlock<byte>& Data)
{
    Padding(Data, m_Rate, m_Domain);
    Sponge<T>(Data, m_Rate, m_NumRounds, m_DigestSize);
}

template class Keccak<word64>;
template class Keccak<word32>;
template class Keccak<word16>;
template class Keccak<byte>;
#include "Modes.h"
#include "Exception.h"

void ctr_increment(byte* ctr, int blockSize)
{
	for (int i = blockSize - 1; i >= 0; i--)
	{
		if (ctr[i] == 0xFF)
		{
			ctr[i] = 0x00;
			continue;
		}

		ctr[i]++;
		break;
	}
}

using namespace LockdownSSL::EncryptionModes;

CTR::CTR(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte>& Nonce) : cipher(Cipher)
{
    LOCKDOWNSSL_ASSERT(Nonce.size() == Cipher.getBlockSize(), LockdownSSL::Exceptions::InvalidDataFormatException("IV length != Cipher Blocksize"));

    nonce = new byte[cipher.getBlockSize()];
    ctr = new byte[cipher.getBlockSize()];

    for(int i = 0; i < cipher.getBlockSize(); i++)
    {
        nonce[i] = Nonce[i];
        ctr[i] = nonce[i];
    }

    ctrptr = 0;
    cipher.encrypt(ctr);
    ctr_increment(nonce, cipher.getBlockSize());
}

std::vector<byte> CTR::getOutput()
{
    return outBuffer;
}

void CTR::stream(byte& data)
{
    if(ctrptr == cipher.getBlockSize())
    {
        ctrptr = 0;
        
        for(int i = 0; i < cipher.getBlockSize(); i++)
            ctr[i] = nonce[i];
        
        cipher.encrypt(ctr);
        ctr_increment(nonce, cipher.getBlockSize());
    }

    outBuffer.push_back((data ^ ctr[ctrptr++]));
}

void CTR::stream(std::vector<byte>& data)
{
    outBuffer.reserve(data.size());

    for(word64 i = 0; i < data.size(); i++)
        stream(data[i]);
}
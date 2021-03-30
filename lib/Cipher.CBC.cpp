#include "Modes.h"
#include "Exception.h"

using namespace LockdownSSL::EncryptionModes;

std::vector<byte> CBC::encrypt(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> data, std::vector<byte> IV)
{
	int blockSize = Cipher.getBlockSize();
	word64 dataSize = data.size();

	LOCKDOWNSSL_ASSERT(IV.size() == blockSize, LockdownSSL::Exceptions::InvalidDataFormatException("IV != BlockSize"));
	LOCKDOWNSSL_ASSERT(dataSize % blockSize == 0, LockdownSSL::Exceptions::InvalidDataFormatException("Data size is not a multiple of the Blocksize"));

	byte* tmp = new byte[blockSize];

	for (word64 i = 0; i < blockSize; i++)
		tmp[i] = data[i];

	word64 numParts = dataSize / blockSize;

	for (word64 i = 0; i < numParts; i++)
	{
		for (int a = 0; a < blockSize; a++)
			tmp[a] ^= i == 0 ? IV[a] : data[i * blockSize + a];

		Cipher.encrypt(tmp);

		for (int b = 0; b < blockSize; b++)
			data[i * blockSize + b] = tmp[b];
	}

	delete[] tmp;

	return data;
}

std::vector<byte> CBC::decrypt(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> data, std::vector<byte> IV)
{
	int blockSize = Cipher.getBlockSize();
	word64 dataSize = data.size();

	LOCKDOWNSSL_ASSERT(IV.size() == blockSize, LockdownSSL::Exceptions::InvalidDataFormatException("IV != BlockSize"));
	LOCKDOWNSSL_ASSERT(dataSize % blockSize == 0, LockdownSSL::Exceptions::InvalidDataFormatException("Data size is not a multiple of the Blocksize"));

	byte* tmp = new byte[blockSize];
	byte* prev = new byte[blockSize];

	for (int i = 0; i < blockSize; i++)
	{
		tmp[i] = data[i];
		prev[i] = data[i];
	}

	word64 numParts = dataSize / blockSize;
	byte buf;
	
	for (word64 i = 0; i < numParts; i++)
	{
		Cipher.decrypt(tmp);

		for (int a = 0; a < blockSize; a++)
		{
			if (i == 0)
			{
				data[a] = tmp[a] ^ IV[a];
				tmp[a] = data[(i + 1) * blockSize + a];
			}
			else
			{
				buf = data[i * blockSize + a];
				data[i * blockSize + a] = tmp[a] ^ prev[a];
				prev[a] = buf;

				if(i != numParts - 1)
					tmp[a] = data[(i + 1) * blockSize + a];
			}
		}
	}

	delete[] tmp;
	delete[] prev;

	return data;
}

/*-----------------------------------*/

std::vector<byte> CBC_MAC::getMac(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> data)
{
	int blockSize = Cipher.getBlockSize();
	word64 dataSize = data.size();

	auto tmp = std::vector<byte>(blockSize);

	for (int i = 0; i < blockSize; i++)
		tmp[i] = 0;

	auto enc = CBC::encrypt(Cipher, data, tmp);
	
	for (int i = dataSize - blockSize, c = 0; i < dataSize; i++, c++)
		tmp[c] = enc[i];

	return tmp;
}
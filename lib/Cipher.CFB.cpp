#include "Modes.h"
#include "Exception.h"

using namespace LockdownSSL::EncryptionModes;

std::vector<byte> CFB::encrypt(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> data, std::vector<byte> IV)
{
	int blockSize = Cipher.getBlockSize();
	word64 dataSize = data.size();
	word64 modifiedBytes = 0;

	LOCKDOWNSSL_ASSERT(IV.size() == blockSize, LockdownSSL::Exceptions::InvalidDataFormatException("IV != BlockSize"));

	byte* tmp = new byte[blockSize];

	while (modifiedBytes < dataSize)
	{
		for (int i = 0; i < blockSize; i++)
			tmp[i] = modifiedBytes == 0 ? IV[i] : data[modifiedBytes - blockSize + i];
	
		Cipher.encrypt(tmp);

		for (int i = 0; i < blockSize && modifiedBytes < dataSize; i++, modifiedBytes++)
		{
			data[modifiedBytes] ^= tmp[i];
		}
	}

	delete[] tmp;
	return data;
}

std::vector<byte> CFB::decrypt(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> data, std::vector<byte> IV)
{
	int blockSize = Cipher.getBlockSize();
	word64 dataSize = data.size();
	word64 modifiedBytes = 0;

	LOCKDOWNSSL_ASSERT(IV.size() == blockSize, LockdownSSL::Exceptions::InvalidDataFormatException("IV != BlockSize"));

	byte* tmp = new byte[blockSize];
	byte buf;

	for (int i = 0; i < blockSize; i++)
		tmp[i] = IV[i];

	while (modifiedBytes < dataSize)
	{
		Cipher.encrypt(tmp);

		for (int i = 0; i < blockSize && modifiedBytes < dataSize; i++, modifiedBytes++)
		{
			buf = data[modifiedBytes];
			data[modifiedBytes] ^= tmp[i];
			tmp[i] = buf;
		}
	}

	delete[] tmp;
	return data;
}
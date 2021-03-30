#include "Modes.h"
#include "Exception.h"

using namespace LockdownSSL::EncryptionModes;

std::vector<byte> ECB::encrypt(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> Data)
{
	word64 dataSize = Data.size();

	LOCKDOWNSSL_ASSERT(dataSize % Cipher.getBlockSize() == 0, LockdownSSL::Exceptions::InvalidDataFormatException("DataSize is not a multiple of the Blocksize"));

	byte* data = new byte[dataSize];

	for (word64 i = 0; i < dataSize; i++)
		data[i] = Data[i];

	int blockSize = Cipher.getBlockSize();
	word64 numParts = dataSize / blockSize;

	for (word64 i = 0; i < numParts; i++)
		Cipher.encrypt(data + (i * blockSize));

	auto out = std::vector<byte>(dataSize);
	for (word64 i = 0; i < dataSize; i++)
		out[i] = data[i];

	delete[] data;

	return out;
}

std::vector<byte> ECB::decrypt(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> Data)
{
	word64 dataSize = Data.size();

	LOCKDOWNSSL_ASSERT(dataSize % Cipher.getBlockSize() == 0, LockdownSSL::Exceptions::InvalidDataFormatException("DataSize is not a multiple of the Blocksize"));

	byte* data = new byte[dataSize];

	for (word64 i = 0; i < dataSize; i++)
		data[i] = Data[i];

	int blockSize = Cipher.getBlockSize();
	word64 numParts = dataSize / blockSize;

	for (word64 i = 0; i < numParts; i++)
		Cipher.decrypt(data + (i * blockSize));

	auto out = std::vector<byte>(dataSize);
	for (word64 i = 0; i < dataSize; i++)
		out[i] = data[i];

	delete[] data;

	return out;
}
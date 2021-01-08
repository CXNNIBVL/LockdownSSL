#include "Modes.h"
#include "Exception.h"

namespace LockdownSSL
{
	namespace EncryptionModes
	{
		std::vector<byte> OFB::stream(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> data, std::vector<byte> IV)
		{
			word64 dataSize = data.size();
			int blockSize = Cipher.getBlockSize();

			LOCKDOWNSSL_ASSERT(IV.size() == blockSize, LockdownSSL::Exceptions::InvalidDataFormatException("IV length != Cipher Blocksize"));

			byte* tmp = new byte[blockSize];
			for (int i = 0; i < blockSize; i++)
				tmp[i] = IV[i];

			word64 processedBytes = 0;

			while (processedBytes < dataSize)
			{
				Cipher.encrypt(tmp);

				for (int i = 0; i < blockSize && processedBytes < dataSize; i++, processedBytes++)
					data[processedBytes] ^= tmp[i];
			}

			delete[] tmp;
			return data;
		}
	}
}

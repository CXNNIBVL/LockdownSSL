// #include "Modes.h"
// #include "Exception.h"

// void ctr_increment(std::vector<byte>& ctr, int ctrBytes_Size, int blockSize)
// {
// 	for (int i = blockSize - 1; i >= 0 + (blockSize - ctrBytes_Size); i--)
// 	{
// 		if (ctr[i] == 0xFF)
// 		{
// 			ctr[i] = 0x00;
// 			continue;
// 		}

// 		ctr[i]++;
// 		break;
// 	}
// }

// namespace LockdownSSL
// {
// 	namespace EncryptionModes
// 	{
// 		std::vector<byte> CTR::stream(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> data, std::vector<byte> Nonce, unsigned int ctrBytes_Size)
// 		{
// 			word64 dataSize = data.size();
// 			int blockSize = Cipher.getBlockSize();

// 			LOCKDOWNSSL_ASSERT(Nonce.size() == blockSize, LockdownSSL::Exceptions::InvalidDataFormatException("Nonce size != Blocksize"));
// 			LOCKDOWNSSL_ASSERT(ctrBytes_Size <= blockSize, LockdownSSL::Exceptions::InvalidDataFormatException("ctrBytes_Size > Blocksize"));

// 			byte* tmp = new byte[blockSize];
// 			for (int i = 0; i < blockSize; i++)
// 				tmp[i] = Nonce[i];

// 			word64 processedBytes = 0;
			
// 			while (processedBytes < dataSize)
// 			{
// 				Cipher.encrypt(tmp);

// 				ctr_increment(Nonce, ctrBytes_Size, blockSize);

// 				for (int i = 0; i < blockSize && processedBytes < dataSize; i++, processedBytes++)
// 				{
// 					data[processedBytes] ^= tmp[i];
// 					tmp[i] = Nonce[i];
// 				}
// 			}

// 			delete[] tmp;
// 			return data;
// 		}
// 	}
// }

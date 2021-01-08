#include "Modes.h"

void cmac_padding(word64 pad_bytes, std::vector<byte>& Data)
{
	word64 initial_size = Data.size();

	Data.resize(initial_size + pad_bytes);

	Data[initial_size] = 0x80;
}

void left_shift_array(byte* arr, int blockSize)
{
	for (int i = 0; i < blockSize - 1; i++)
	{
		arr[i] = (arr[i] << 1) | (arr[i + 1] >> 7);
	}

	arr[blockSize - 1] <<= 1;
}

byte* cmac_genSubkey(LockdownSSL::Cipher::ICipher& Cipher, int flag)
{
	int blockSize = Cipher.getBlockSize();

	byte RB = 0x87;
	byte* K = new byte[blockSize];

	for (int i = 0; i < blockSize; i++)
		K[i] = 0;

	Cipher.encrypt(K);

	int msb_flag = (K[0] >> 7) != 0 ? 1 : 0;

	left_shift_array(K, blockSize);

	if (msb_flag == 1)
	{
		K[blockSize - 1] ^= RB;
	}

	if (flag == 0)
		return K;

	msb_flag = (K[0] >> 7) != 0 ? 1 : 0;

	left_shift_array(K, blockSize);

	if (msb_flag == 1)
	{
		K[blockSize - 1] ^= RB;
	}

	return K;
}

namespace LockdownSSL
{
	namespace EncryptionModes
	{
		std::vector<byte> CMAC::getMac(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> data)
		{
			int subkey_flag;
			word64 size_padding;
			word64 dataSize = data.size();
			int blockSize = Cipher.getBlockSize();
			
			if (dataSize == 0) { size_padding = blockSize; subkey_flag = 1; }
			else if ((dataSize % blockSize) == 0 && dataSize > 0) { size_padding = 0; subkey_flag = 0; }
			else
			{
				size_padding = blockSize - (dataSize % blockSize);
				subkey_flag = 1;
			}
			
			if (size_padding != 0)
			{
				cmac_padding(size_padding, data);
			}
			
			byte* subkey = cmac_genSubkey(Cipher, subkey_flag);
			
			size_t num_parts = data.size() / blockSize;
			byte* tag = new byte[blockSize];
			
			for (int i = 0; i < blockSize; i++)
			{
				tag[i] = data[i];
			}
			
			for (size_t i = 0; i < num_parts; i++)
			{
				if (i != 0)
				{
					for (int b = 0; b < blockSize; b++)
					{
						tag[b] ^= data[(i * blockSize) + b];
					}
				}
			
				if (i == num_parts - 1)
				{
					for (int c = 0; c < blockSize; c++)
					{
						tag[c] ^= subkey[c];
					}
				}
			
				Cipher.encrypt(tag);
			}
			
			delete[] subkey;
			
			auto out = std::vector<byte>(blockSize);
			for (int i = 0; i < blockSize; i++)
			{
				out[i] = tag[i];
			}
			
			return out;
		}
	}
}

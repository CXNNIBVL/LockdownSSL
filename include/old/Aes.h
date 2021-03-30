#pragma once

#include "ICipher.h"

namespace LockdownSSL
{
	namespace Cipher
	{
		class Aes : public ICipher_128b
		{
		public:
			static Aes getInstance_128(byte* key);
			static Aes getInstance_192(byte* key);
			static Aes getInstance_256(byte* key);

			void encrypt(byte* Data);
			void decrypt(byte* Data);

			~Aes()
			{
				delete[] expandedKeys;
			}

		private:
			int expKeyBytes;
			byte* expandedKeys;
			int numRounds;

			Aes(int ExpBytesToGenerate, byte* ExpandedKeys, int NumRounds)
			{
				expKeyBytes = ExpBytesToGenerate;
				expandedKeys = ExpandedKeys;
				numRounds = NumRounds;
			}
		};
	}
}
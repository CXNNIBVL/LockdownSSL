#pragma once

#include "lockdownssl/types.h"

namespace LockdownSSL
{
	namespace Cipher
	{
		class ICipher
		{
		public:
			virtual void encrypt(byte* Data) = 0;
			virtual void decrypt(byte* Data) = 0;
			virtual const int getBlockSize() = 0;

		protected:
			ICipher(){}
		};

		class ICipher_128b :public ICipher
		{
		public:
			const int getBlockSize() { return 16; }

		protected:
			ICipher_128b() {};
		};
	}
}
#ifndef LOCKDOWNSSL_SHA2
#define LOCKDOWNSSL_SHA2

#include "IHash.h"

namespace LockdownSSL
{
	namespace Hash
	{
		class Sha2 : public IHash
		{
		public:
			static Sha2 getInstance_224();
			static Sha2 getInstance_256();
			static Sha2 getInstance_384();
			static Sha2 getInstance_512();
			static Sha2 getInstance_512_224();
			static Sha2 getInstance_512_256();

			std::vector<byte> getHash(std::vector<byte>& Data);
			const int getBlockSize();

		private:
			int ommit_H;
			const word32* hbuf_32b;
			const word64* hbuf_64b;
			int blockSize;

			Sha2(int Ommit_H, const word32* Hbuf_32b, int Blocksize);
			Sha2(int Ommit_H, const word64* Hbuf_64b, int Blocksize);
		};
	}
}

#endif
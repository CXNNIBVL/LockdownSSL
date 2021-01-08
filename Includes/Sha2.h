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

			std::vector<byte> getHash(std::vector<byte>);
			const int getBlockSize();

		private:
			bool is32bInstance;
			int ommit_H;
			std::vector<word32> hbuf_32b;
			std::vector<word64> hbuf_64b;
			int blockSize;

			Sha2(bool Is32bInstance, int Ommit_H, std::vector<word32> Hbuf_32b, std::vector<word64> Hbuf_64b, int Blocksize);
		};
	}
}

#endif
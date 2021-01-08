#ifndef LOCKDOWNSSL_SHA3
#define LOCKDOWNSSL_SHA3

#include "IHash.h"

namespace LockdownSSL
{
	namespace Hash
	{
		class Sha3 : public IHash
		{
		public:
			static Sha3 getInstance_224();
			static Sha3 getInstance_256();
			static Sha3 getInstance_384();
			static Sha3 getInstance_512();

			std::vector<byte> getHash(std::vector<byte> data);
			const int getBlockSize();


		private:
			word64 output_length;
			int blockSize;

			Sha3(word64 Output_Length, int Blocksize)
			{
				output_length = Output_Length;
				blockSize = Blocksize;
			}
		};

		class Shake
		{
		public:
			static Shake getInstance_128();
			static Shake getInstance_256();

			std::vector<byte> getHash(std::vector<byte> data, word64 outBytes, word64 outBits);

		private:
			int rate;

			Shake(int Rate)
			{
				rate = Rate;
			}
		};
	}
}

#endif
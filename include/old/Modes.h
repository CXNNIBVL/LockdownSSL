#ifndef LOCKDOWNSSL_MODES
#define LOCKDOWNSSL_MODES

#include <vector>
#include "ICipher.h"

namespace LockdownSSL
{
	namespace EncryptionModes
	{
		class ECB
		{
		public:
			static std::vector<byte> encrypt(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> data);
			static std::vector<byte> decrypt(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> data);

		private:
			ECB();
		};

		class CBC
		{
		public:
			static std::vector<byte> encrypt(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> data, std::vector<byte> IV);
			static std::vector<byte> decrypt(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> data, std::vector<byte> IV);

		private:
			CBC();
		};

		class CBC_MAC
		{
		public:
			static std::vector<byte> getMac(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> data);

		private:
			CBC_MAC();
		};

		class CMAC
		{
		public:
			static std::vector<byte> getMac(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> data);

		private:
			CMAC();
		};

		class CFB
		{
		public:
			static std::vector<byte> encrypt(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> data, std::vector<byte> IV);
			static std::vector<byte> decrypt(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> data, std::vector<byte> IV);

		private:
			CFB();
		};

		class OFB
		{
		public:
			OFB(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte>& IV);

			~OFB()
			{
				delete[] iv;
			}

			void stream(std::vector<byte>& data);
			void stream(byte& data);

			OFB& operator <<(std::vector<byte>& data)
			{
				stream(data);
				return *this;
			}

			OFB& operator <<(byte& data)
			{
				stream(data);
				return *this;
			}

			std::vector<byte> getOutput();
			void reset();

		private:
			LockdownSSL::Cipher::ICipher& cipher;
			std::vector<byte> orgIV;
			byte ivptr;
			byte* iv;
			std::vector<byte> outBuffer;
		};

		class CTR
		{
		public:
			CTR(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte>& Nonce);

			~CTR()
			{
				delete[] nonce;
				delete[] ctr;
			}

			void stream(std::vector<byte>& data);
			void stream(byte& data);

			CTR& operator <<(std::vector<byte>& data)
			{
				stream(data);
				return *this;
			}

			CTR& operator <<(byte& data)
			{
				stream(data);
				return *this;
			}

			std::vector<byte> getOutput();

		private:
			LockdownSSL::Cipher::ICipher& cipher;
			byte* nonce;

			byte* ctr;
			byte ctrptr;

			std::vector<byte> outBuffer;
		};
	}
}

#endif

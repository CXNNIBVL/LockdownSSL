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
			static std::vector<byte> stream(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> data, std::vector<byte> IV);
		private:
			OFB();
		};

		class CTR
		{
		public:
			CTR(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte> Nonce, unsigned int ctrBytes_Size);

			std::vector<byte> stream(std::vector<byte>& data);
			std::vector<byte> stream(byte data);

			CTR& operator <<(byte& data)
			{
				stream(data);
				return *this;
			}

			CTR& operator <<(std::vector<byte>& data)
			{
				stream(data);
				return *this;
			}

			std::vector<byte> getOutput();

		private:
			std::vector<byte> buffer;
			std::vector<byte> nonce;
			LockdownSSL::Cipher::ICipher& cipher;
			unsigned int ctrBytes_size;
		};
	}
}

#endif

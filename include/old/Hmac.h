#pragma once

#include "IHash.h"

namespace LockdownSSL
{
	namespace Hash
	{
		class HMAC
		{
		public:
			static std::vector<byte> getMac(IHash& HashFunction, std::vector<byte>& Data, std::vector<byte>& Key);

		private:
			HMAC(){}
		};
	}
}

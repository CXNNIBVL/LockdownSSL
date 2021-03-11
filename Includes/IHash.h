#pragma once

#include <vector>
#include "types.h"

namespace LockdownSSL
{
	namespace Hash
	{
		class IHash
		{
		public:
			virtual std::vector<byte> getHash(std::vector<byte>& data) = 0;
			virtual const int getBlockSize() = 0;
		};
	}
}
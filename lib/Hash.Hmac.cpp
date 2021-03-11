#include "Hmac.h"

using namespace LockdownSSL::Hash;

std::vector<byte> prepare_key(IHash& HashFunction, std::vector<byte>& Key)
{
	const int blockSize = HashFunction.getBlockSize();

	if (Key.size() == blockSize)
	{
		return Key;
	}
	else if (Key.size() < blockSize)
	{
		word32 pad_size = blockSize - (Key.size() % blockSize);
		Key.resize(Key.size() + pad_size);
		return Key;
	}
	else
	{
		auto tmp =HashFunction.getHash(Key);
		return prepare_key(HashFunction, tmp);
	}
}

std::vector<byte> HMAC::getMac(IHash& HashFunction, std::vector<byte>& Data, std::vector<byte>& Key)
{
	std::vector<byte> key = prepare_key(HashFunction, Key);

	std::vector<byte> ipad;
	ipad.reserve(key.size() + Data.size());

	ipad.insert(ipad.begin(), key.begin(), key.end());
	ipad.insert(ipad.end(), Data.begin(), Data.end());

	for (word32 i = 0; i < key.size(); i++)
	{
		ipad[i] ^= 0x36;
	}

	ipad = HashFunction.getHash(ipad);

	std::vector<byte> opad;
	opad.reserve(key.size() + ipad.size());

	opad.insert(opad.begin(), key.begin(), key.end());
	opad.insert(opad.end(), ipad.begin(), ipad.end());

	for (word32 i = 0; i < key.size(); i++)
	{
		opad[i] ^= 0x5c;
	}

	return HashFunction.getHash(opad);
}
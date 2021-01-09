#include "Modes.h"
#include "Exception.h"

using namespace LockdownSSL::EncryptionModes;

OFB::OFB(LockdownSSL::Cipher::ICipher& Cipher, std::vector<byte>& IV) : cipher(Cipher)
{
	LOCKDOWNSSL_ASSERT(IV.size() == Cipher.getBlockSize(), LockdownSSL::Exceptions::InvalidDataFormatException("IV length != Cipher Blocksize"));
	
	iv = new byte[cipher.getBlockSize()];
	ivptr = 0;
	orgIV = IV;

	for(int i = 0; i < cipher.getBlockSize(); i++)
		iv[i] = orgIV[i];

	cipher.encrypt(iv);
}

std::vector<byte> OFB::getOutput()
{
	return outBuffer;
}

void OFB::stream(byte& data)
{
	if(ivptr == cipher.getBlockSize())
	{
		ivptr = 0;
		cipher.encrypt(iv);
	}

	outBuffer.push_back((data ^ iv[ivptr++]));
}

void OFB::stream(std::vector<byte>& data)
{
	outBuffer.reserve(data.size());

	for(word64 i = 0; i < data.size(); i++)
		stream(data[i]);
}

void OFB::reset()
{
	for(int i = 0; i < cipher.getBlockSize(); i++)
		iv[i] = orgIV[i];

	outBuffer.resize(0);
}
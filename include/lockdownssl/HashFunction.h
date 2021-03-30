#include "lockdownssl/SecureBlock.h"

namespace LockdownSSL
{
    class HashFunction
    {
    public:

        virtual void Digest(SecureBlock<byte>& Data) = 0;

        virtual size_t DigestSize() = 0;

        virtual size_t BlockSize() = 0;
    };
}
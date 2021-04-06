#pragma once

#include "lockdownssl/SecureBlock.h"

namespace LockdownSSL
{
    class HashFunction
    {
    public:
        virtual SecureBlock<byte> Digest() = 0;
        virtual void Put(const SecureBlock<byte>& Data) { m_Data.AssignBlock(Data); }
        virtual size_t DigestSize() = 0;
        virtual size_t BlockSize() = 0;
    
    protected:
        SecureBlock<byte> m_Data;
    };
}
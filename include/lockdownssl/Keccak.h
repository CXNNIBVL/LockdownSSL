#pragma once

#include "lockdownssl/KeccakCore.h"
#include "lockdownssl/HashFunction.h"

namespace LockdownSSL
{
    class Keccak : private Keccak_P_1600, public HashFunction
    {
    public:

        SecureBlock<byte> Digest() override { Hash(m_Data); return m_Data; }
        size_t DigestSize() { return GetDigestSize(); }
        size_t BlockSize() { return GetRate(); }
    
    protected:
        Keccak(byte Rate, byte Domain, size_t DigestSize) 
            : Keccak_P_1600(Rate, 24, Domain, DigestSize){}
    };

    class Keccak_224 : public Keccak
    {
    public:
        Keccak_224() : Keccak(144, 0x01, 28){}
    };

    class Keccak_256 : public Keccak
    {
    public:
        Keccak_256() : Keccak(136, 0x01, 32){}
    };

    class Keccak_384 : public Keccak
    {
    public:
        Keccak_384() : Keccak(104, 0x01, 48){}
    };

    class Keccak_512 : public Keccak
    {
    public:
        Keccak_512() : Keccak(72, 0x01, 64){}
    };
}
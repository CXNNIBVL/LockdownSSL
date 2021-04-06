#pragma once

#include "lockdownssl/KeccakCore.h"
#include "lockdownssl/HashFunction.h"

namespace LockdownSSL
{
    class Sha3 : private Keccak_P_1600, public HashFunction
    {
    public:

        SecureBlock<byte> Digest() override { Hash(m_Data); return m_Data; }
        size_t DigestSize() { return GetDigestSize(); }
        size_t BlockSize() { return GetRate(); }

    protected:
        Sha3(byte Rate, byte Domain, size_t DigestSize)
            : Keccak_P_1600(Rate, 24, Domain, DigestSize){}
    };

    class Sha3_224 : public Sha3
    {
    public:
        Sha3_224() : Sha3(144, 0x06, 28){}
    };

    class Sha3_256 : public Sha3
    {
    public:
        Sha3_256() : Sha3(136, 0x06, 32){}
    };

    class Sha3_384 : public Sha3
    {
    public:
        Sha3_384() : Sha3(104, 0x06, 48){}
    };

    class Sha3_512 : public Sha3
    {
    public:
        Sha3_512() : Sha3(72, 0x06, 64){}
    };

    class Shake_128 : public Sha3
    {
    public:
        explicit Shake_128(size_t DigestSize) : Sha3(168, 0x1f, DigestSize){}
    };

    class Shake_256 : public Sha3
    {
    public:
        explicit Shake_256(size_t DigestSize) : Sha3(136, 0x1f, DigestSize){}
    };
}
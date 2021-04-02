#pragma once

#include "lockdownssl/HashFunction.h"

#define CSHAKE_DOMAIN 0x04

namespace LockdownSSL
{
    template<typename T>
    class Keccak : public HashFunction
    {
    public:

        Keccak() = delete;

        explicit Keccak(byte Rate, byte NumRounds, byte Domain, size_t DigestSize)
            : m_Rate(Rate), m_NumRounds(NumRounds), m_Domain(Domain), m_DigestSize(DigestSize) {}

        void Digest(SecureBlock<byte>& Data) override;

        size_t DigestSize() override { return m_DigestSize; }
        size_t BlockSize() override { return m_Rate; }

    private:
        byte m_Rate;
        byte m_NumRounds;
        byte m_Domain;
        size_t m_DigestSize;
    };

    //Supported Keccak-P instances
    typedef Keccak<word64> Keccak_P_1600;
    typedef Keccak<word32> Keccak_P_800;
    typedef Keccak<word16> Keccak_P_400;
    typedef Keccak<byte> Keccak_P_200;

    //Supported Sha3 instances
    class Sha3_224 : public Keccak_P_1600
    {
    public:
        Sha3_224() : Keccak_P_1600(144, 24, 0x06, 28){}
    };

    class Sha3_256 : public Keccak_P_1600
    {
    public:
        Sha3_256() : Keccak_P_1600(136, 24, 0x06, 32){}
    };

    class Sha3_384 : public Keccak_P_1600
    {
    public:
        Sha3_384() : Keccak_P_1600(104, 24, 0x06, 48){}
    };

    class Sha3_512 : public Keccak_P_1600
    {
    public:
        Sha3_512() : Keccak_P_1600(72, 24, 0x06, 64){}
    };

    template<size_t SDigest=0>
    class Shake_128 : public Keccak_P_1600
    {
    public:
        Shake_128() : Keccak_P_1600(168, 24, 0x1f, SDigest){}

        explicit Shake_128(size_t DigestSize) : Keccak_P_1600(168, 24, 0x1f, DigestSize){}
    };

    template<size_t SDigest=0>
    class Shake_256 : public Keccak_P_1600
    {
    public:
        Shake_256() : Keccak_P_1600(168, 24, 0x1f, SDigest){}

        explicit Shake_256(size_t DigestSize) : Keccak_P_1600(136, 24, 0x1f, DigestSize){}
    };

    //Supported Keccak instances
    class Keccak_224 : public Keccak_P_1600
    {
    public:
        Keccak_224() : Keccak_P_1600(144, 24, 0x01, 28){}
    };

    class Keccak_256 : public Keccak_P_1600
    {
    public:
        Keccak_256() : Keccak_P_1600(136, 24, 0x01, 32){}
    };

    class Keccak_384 : public Keccak_P_1600
    {
    public:
        Keccak_384() : Keccak_P_1600(104, 24, 0x01, 48){}
    };

    class Keccak_512 : public Keccak_P_1600
    {
    public:
        Keccak_512() : Keccak_P_1600(72, 24, 0x01, 64){}
    };
}

#undef CSHAKE_DOMAIN
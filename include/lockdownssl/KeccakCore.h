#pragma once

#include "lockdownssl/HashFunction.h"

namespace LockdownSSL
{
    template<typename T>
    class Keccak : public HashFunction
    {
    public:
        Keccak() : m_Rate(0), m_NumRounds(0), m_Domain(0), m_DigestSize(0){}

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
}
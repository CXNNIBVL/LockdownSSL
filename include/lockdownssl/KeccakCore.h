#pragma once

#include "lockdownssl/SecureBlock.h"

namespace LockdownSSL
{
    template<typename T>
    class KeccakSponge
    {
    public:
        KeccakSponge() : m_Rate(0), m_NumRounds(0), m_Domain(0), m_DigestSize(0){}
        explicit KeccakSponge(byte Rate, byte NumRounds, byte Domain, size_t DigestSize)
            : m_Rate(Rate), m_NumRounds(NumRounds), m_Domain(Domain), m_DigestSize(DigestSize){}

        void Hash(SecureBlock<byte>& Data);

        void SetRate(byte Rate) { m_Rate = Rate; }
        byte GetRate() { return m_Rate; }
        
        void SetNumRounds(byte NumRounds) { m_NumRounds = NumRounds; }
        void SetDomain(byte Domain) { m_Domain = Domain; }

        void SetDigestSize(size_t DigestSize) { m_DigestSize = DigestSize; }
        size_t GetDigestSize() { return m_DigestSize; }

    private:
        byte m_Rate;
        byte m_NumRounds;
        byte m_Domain;
        size_t m_DigestSize;
    };

    //Supported Keccak-P instances
    typedef KeccakSponge<word64> Keccak_P_1600;
    typedef KeccakSponge<word32> Keccak_P_800;
    typedef KeccakSponge<word16> Keccak_P_400;
    typedef KeccakSponge<byte> Keccak_P_200;
}
#pragma once

#include <string>

#include "lockdownssl/KeccakCore.h"
#include "lockdownssl/HashFunction.h"


namespace LockdownSSL
{
    template<byte Rate=168, byte IntermDigestSize=32, byte NumRounds=12>
    class KangarooTwelve : private Keccak_P_1600, public HashFunction
    {
    public:
        KangarooTwelve() : KangarooTwelve(std::string(""), 0) {}

        KangarooTwelve(std::string CustomisationString, size_t DigestSize)
            : m_CustomisationString(CustomisationString), m_FinalDigestSize(DigestSize)
        { SetRate(Rate); SetNumRounds(NumRounds); }

        void SetCustomisationString(std::string CustomisationString) { m_CustomisationString = CustomisationString; }
        void SetDigestSize(size_t DigestSize) { m_FinalDigestSize = DigestSize; }

        SecureBlock<byte> Digest();
        void Put(const SecureBlock<byte>& Data) override;
        size_t DigestSize() { return m_FinalDigestSize; };
        size_t BlockSize() { return 8192; };

    private:
        std::string m_CustomisationString;
        size_t m_FinalDigestSize;
    };

    typedef KangarooTwelve<136, 64, 14> MarsupilamiFourteen;
}
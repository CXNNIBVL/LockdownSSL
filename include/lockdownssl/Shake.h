#pragma once

#include "lockdownssl/KeccakCore.h"

namespace LockdownSSL
{
    class Shake_128 : public Keccak_P_1600
    {
    public:
        explicit Shake_128(size_t DigestSize) : Keccak_P_1600(168, 24, 0x1f, DigestSize){}
    };
    
    class Shake_256 : public Keccak_P_1600
    {
    public:
        explicit Shake_256(size_t DigestSize) : Keccak_P_1600(136, 24, 0x1f, DigestSize){}
    };

    
    class cShake_128 : public HashFunction
    {
    public:
        explicit cShake_128(size_t DigestSize, const char* CustomisationString="")
            : cShake_128(DigestSize, "", CustomisationString){}

        void Digest(SecureBlock<byte>& Data) override;
        size_t DigestSize() override { return m_Keccak.DigestSize(); }
        size_t BlockSize() override { return m_Keccak.BlockSize(); }

    protected:
        explicit cShake_128(size_t DigestSize, const char* FunctionName, const char* CustomisationString)
            : m_FunctionName(FunctionName), m_Customisation(CustomisationString)
        {
            if(std::strlen(m_FunctionName) == 0 && std::strlen(m_Customisation) == 0)
            {
                m_EncodeString = false;
                m_Keccak = Shake_128(DigestSize); 
            }
            else
            {
                m_EncodeString = true;
                m_Keccak = Keccak_P_1600(168, 24, 0x04, DigestSize);
            }
        } 

    private:
        const char* m_FunctionName;
        const char* m_Customisation;
        bool m_EncodeString;
        Keccak_P_1600 m_Keccak;
    };

    class cShake_256 : public HashFunction
    {
    public:
        explicit cShake_256(size_t DigestSize, const char* CustomisationString="")
            : cShake_256(DigestSize, "", CustomisationString){}

        void Digest(SecureBlock<byte>& Data) override;
        size_t DigestSize() override { return m_Keccak.DigestSize(); }
        size_t BlockSize() override { return m_Keccak.BlockSize(); }

    protected:
        explicit cShake_256(size_t DigestSize, const char* FunctionName, const char* CustomisationString)
            : m_FunctionName(FunctionName), m_Customisation(CustomisationString)
        {
            if(std::strlen(m_FunctionName) == 0 && std::strlen(m_Customisation) == 0)
            {
                m_EncodeString = false;
                m_Keccak = Shake_256(DigestSize); 
            }
            else
            {
                m_EncodeString = true;
                m_Keccak = Keccak_P_1600(136, 24, 0x04, DigestSize);
            }
        } 

    private:
        const char* m_FunctionName;
        const char* m_Customisation;
        bool m_EncodeString;
        Keccak_P_1600 m_Keccak;
    };
}
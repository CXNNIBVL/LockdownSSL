#pragma once

#include <string>

#include "pipeline/TransformationFilter.h"

namespace LockdownSSL::Pipeline
{
    class HexEncoder : public TransformationFilter
    {
    public:

        enum Case { UPPERCASE = 0, LOWERCASE = 1 };

        HexEncoder() 
            : m_Case(UPPERCASE), m_GroupSize(1),
            m_Header(""), m_Seperator(":"), m_Terminator("") {}

        ~HexEncoder(){};

        HexEncoder& setCase(Case c) { m_Case = c; return *this; }
        HexEncoder& setGroupSize(const size_t GroupSize) { m_GroupSize = GroupSize == 0 ? 1 : GroupSize; return *this; }
        HexEncoder& setHeader(const std::string& Header) { m_Header = Header; return *this; }
        HexEncoder& setSeperator(const std::string& Seperator) { m_Seperator = Seperator; return *this; }
        HexEncoder& setTerminator(const std::string& Terminator) { m_Terminator = Terminator; return *this; }

        void ProcessData(SecureBlock<byte>& Data) override;

    private:
        Case m_Case;
        size_t m_GroupSize;
        std::string m_Header, m_Seperator, m_Terminator;
    };

    class HexDecoder : public TransformationFilter
    {
    public:

        HexDecoder() = default;
        ~HexDecoder(){};

        void ProcessData(SecureBlock<byte>& Data) override; 
    };
}
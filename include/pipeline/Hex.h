#pragma once

#include <string>

#include "pipeline/TransformationFilter.h"

namespace LockdownSSL::Pipeline
{
    class HexEncoder;

    struct HexEncoderConfig
    {
    public:
        friend class HexEncoder;

        enum Case { UPPERCASE = 0, LOWERCASE = 1 };

        HexEncoderConfig
        (
            size_t GroupSize,  Case Case, const std::string& Header,
            const std::string& Seperator, const std::string& Terminator
        )
        : m_Case(Case), m_GroupSize(GroupSize == 0 ? 1 : GroupSize), 
           m_Header(Header), m_Seperator(Seperator), m_Terminator(Terminator) {}

        
    private:
        Case m_Case;
        size_t m_GroupSize;
        const std::string &m_Header, &m_Seperator, &m_Terminator;
    };

    class HexEncoder : public TransformationFilter
    {
    public:

        HexEncoder(HexEncoderConfig& Config, TransformationFilter* AttachedTransformation=nullptr)
        : TransformationFilter(AttachedTransformation), m_Config(Config) {}

        void ProcessData(SecureBlock<byte>& Data) override;

    private:
        HexEncoderConfig& m_Config;
    };

    class HexDecoder : public TransformationFilter
    {
    public:

        HexDecoder(TransformationFilter* AttachedTransformation=nullptr)
            : TransformationFilter(AttachedTransformation) {}

        void ProcessData(SecureBlock<byte>& Data) override; 
    };
}
#pragma once

#include <istream>

#include "pipeline/TransformationFilter.h"

namespace LockdownSSL::Pipeline
{
    class StreamSource;

    struct iStream
    {
    public:

        friend class StreamSource;

        iStream(std::istream& Is, char Delimiter=-1) : m_Is(Is), m_Delimiter(Delimiter) {}

    private:
        std::istream& m_Is;
        char m_Delimiter;
    };

    class StreamSource
    {
    public:

        explicit StreamSource(iStream& Stream, TransformationFilter* AttachedTransformation=nullptr);

        SecureBlock<byte> GetBuffer() { return m_Buffer; }

    private:
        SecureBlock<byte> m_Buffer;
    };
}
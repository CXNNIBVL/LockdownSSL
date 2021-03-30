#pragma once

#include "pipeline/TransformationFilter.h"

namespace LockdownSSL::Pipeline
{
    class ArraySink : public TransformationFilter
    {
    public:

        ArraySink(byte* Buffer, size_t Size)
            : m_Buffer(Buffer), m_Size(Size) {}

        void ProcessData(SecureBlock<byte>& Data) override;

    private:
        byte* m_Buffer;
        size_t m_Size;
    };
}
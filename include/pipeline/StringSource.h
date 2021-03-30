#pragma once

#include <string>

#include "pipeline/TransformationFilter.h"

namespace LockdownSSL::Pipeline
{
    class StringSource
    {
    public:

        StringSource(const byte* Data, size_t Length, TransformationFilter* AttachedTransformation=nullptr);

        StringSource(const char* Data, TransformationFilter* AttachedTransformation=nullptr);

        StringSource(const std::string& Data, TransformationFilter* AttachedTransformation=nullptr) 
            : StringSource(Data.c_str(), AttachedTransformation) {}

        SecureBlock<byte> GetBuffer() { return m_Buffer; }

    private:
        SecureBlock<byte> m_Buffer;
    };
}
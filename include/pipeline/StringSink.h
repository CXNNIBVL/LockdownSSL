#pragma once

#include <string>

#include "pipeline/TransformationFilter.h"

namespace LockdownSSL::Pipeline
{
    class StringSink : public TransformationFilter
    {
    public:

        StringSink(std::string& Buffer)
            : m_Buffer(Buffer) {}

        ~StringSink(){}

        void ProcessData(SecureBlock<byte>& Data) override;

    private:
        std::string& m_Buffer;
    };
}
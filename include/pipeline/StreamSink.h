#pragma once

#include <ostream>

#include "pipeline/TransformationFilter.h"

namespace LockdownSSL::Pipeline
{
    class StreamSink : public TransformationFilter
    {
    public:

        StreamSink(std::ostream& Stream) : m_Stream(Stream) {}

        ~StreamSink(){}

        void ProcessData(SecureBlock<byte>& Data) override;
    
    private:
        std::ostream& m_Stream;
    };
}
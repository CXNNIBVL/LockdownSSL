#pragma once

#include "pipeline/TransformationFilter.h"

namespace LockdownSSL::Pipeline
{
    class Source
    {
    public:
        Source() = default;
        Source(const Source& Other) = delete;
        Source(Source&& Other) = delete;

        SecureBlock<byte> GetBuffer(){ return m_Buffer; }

        Source& operator>(TransformationFilter& AttachedTransformation)
        {
            AttachedTransformation.ProcessData(m_Buffer);
            return *this;
        }

        Source& operator>(TransformationFilter&& AttachedTransformation)
        {
            AttachedTransformation.ProcessData(m_Buffer);
            return *this;
        }

    protected:
        SecureBlock<byte> m_Buffer;
    };
}
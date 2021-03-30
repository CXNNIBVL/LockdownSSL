#pragma once

#include "lockdownssl/types.h"
#include "lockdownssl/SecureBlock.h"

namespace LockdownSSL::Pipeline
{
    class TransformationFilter
    {
    public:

        explicit TransformationFilter(TransformationFilter* AttachedTransformation=nullptr)
            : m_AttatchedTransformation(AttachedTransformation) {}

        virtual ~TransformationFilter() { delete m_AttatchedTransformation; }

        virtual void ProcessData(SecureBlock<byte>& Data) = 0;
        
    protected:
        TransformationFilter* m_AttatchedTransformation;
    };
}
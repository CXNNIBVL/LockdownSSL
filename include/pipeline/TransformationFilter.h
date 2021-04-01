#pragma once

#include "lockdownssl/types.h"
#include "lockdownssl/SecureBlock.h"

namespace LockdownSSL::Pipeline
{
    class TransformationFilter
    {
    public:
        TransformationFilter() = default;
        TransformationFilter(const TransformationFilter& Other) = delete;
        TransformationFilter(TransformationFilter&& Other) = delete;

        virtual ~TransformationFilter(){}

        virtual void ProcessData(SecureBlock<byte>& Data) = 0;
    };
}
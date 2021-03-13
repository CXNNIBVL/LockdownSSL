#pragma once

#include "types.h"
#include "SecureBlock.h"

namespace LockdownSSL
{
    class TransfomationFilter
    {
    public:
        TransfomationFilter(TransfomationFilter* AttachedTransformation)
            : m_AttatchedTransformation(AttachedTransformation) {}

        virtual ~TransfomationFilter() {}

        virtual void ProcessData(SecureBlock<byte>& Data) = 0;
        TransfomationFilter* GetAttachedTransformation() { return m_AttatchedTransformation; }

    private:
        TransfomationFilter* m_AttatchedTransformation;
    };
}
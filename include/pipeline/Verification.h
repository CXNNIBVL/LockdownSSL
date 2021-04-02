#pragma once

#include "pipeline/TransformationFilter.h"

namespace LockdownSSL::Pipeline
{
    class VerificationFilter : public TransformationFilter
    {
    public:
        VerificationFilter(SecureBlock<byte>& Expected, bool& Verified, bool ShouldPipeOnFail)
            : m_Expected(Expected), m_Verified(Verified), m_ShouldPipe(ShouldPipeOnFail){}

        void ProcessData(SecureBlock<byte>& Data) override;
    private:
        SecureBlock<byte>& m_Expected;
        bool& m_Verified;
        bool m_ShouldPipe;
    };
}
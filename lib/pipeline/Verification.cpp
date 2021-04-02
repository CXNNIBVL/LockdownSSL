#include "pipeline/Verification.h"

using namespace LockdownSSL::Pipeline;
using namespace LockdownSSL;

void VerificationFilter::ProcessData(SecureBlock<byte>& Data)
{
    m_Verified = Data == m_Expected;

    if(!m_Verified && !m_ShouldPipe)
        Data.Resize(0);
}
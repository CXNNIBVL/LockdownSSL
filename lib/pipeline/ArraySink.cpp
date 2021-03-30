#include "pipeline/ArraySink.h"

using namespace LockdownSSL::Pipeline;

void ArraySink::ProcessData(SecureBlock<byte>& Data)
{
    if(m_Buffer != nullptr)
    {
        for(size_t i = 0; i < Data.Size() && i < m_Size; i++)
            m_Buffer[i] = Data[i];
    }
}
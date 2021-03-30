#include "pipeline/StringSource.h"
#include "pipeline/StringSink.h"

namespace STL = ::std;
using namespace LockdownSSL::Pipeline;

StringSource::StringSource(const byte* Data, size_t Length, TransformationFilter* AttachedTransformation)
{   
    if(AttachedTransformation)
    {
        m_Buffer = SecureBlock<byte>(Data, Length);

        AttachedTransformation->ProcessData(m_Buffer);
        delete AttachedTransformation;
    }
}

StringSource::StringSource(const char* Data, TransformationFilter* AttachedTransformation)
{
    if(AttachedTransformation)
    {
        size_t len = STL::strlen(Data);
    
        m_Buffer = SecureBlock<byte>(len);
        STL::memcpy(m_Buffer.Data(), Data, len * sizeof(byte));

        AttachedTransformation->ProcessData(m_Buffer);
        delete AttachedTransformation;
    }
}

void StringSink::ProcessData(SecureBlock<byte>& Data)
{
    std::string out( (char*) Data.Data(), Data.Size() );
    m_Buffer = std::move(out);
}
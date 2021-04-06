#include "pipeline/StringSource.h"
#include "pipeline/StringSink.h"

using namespace LockdownSSL::Pipeline;

StringSource::StringSource(const byte* Data, size_t Length)
{   
    m_Buffer = SecureBlock<byte>(Data, Length);
}

StringSource::StringSource(const char* Data)
{
    size_t len = std::strlen(Data);

    m_Buffer = SecureBlock<byte>(len);
    std::memcpy(m_Buffer.Data(), Data, len * sizeof(byte));
}

void StringSink::ProcessData(SecureBlock<byte>& Data)
{
    std::string out( (char*) Data.Data(), Data.Size() );
    m_Buffer = std::move(out);
}
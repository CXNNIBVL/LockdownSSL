#include "pipeline/StreamSource.h"
#include "pipeline/StreamSink.h"

using namespace LockdownSSL::Pipeline;

StreamSource::StreamSource(std::istream& inStream, char Delimiter)
{  
    char c = inStream.get();
    while(c != Delimiter && inStream.good())
    {
        m_Buffer.Grow(1);
        m_Buffer[m_Buffer.Size() - 1] = c;

        c = inStream.get();
    }

    inStream.clear();
}

void StreamSink::ProcessData(SecureBlock<byte>& Data)
{
    if(m_oStream.good())
    {
        m_oStream.write( (const char*) Data.Data(), Data.Size() );
        m_oStream << std::endl;
    }

    m_oStream.clear();
}
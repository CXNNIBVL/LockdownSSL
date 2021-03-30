#include "pipeline/StreamSource.h"
#include "pipeline/StreamSink.h"

using namespace LockdownSSL::Pipeline;

StreamSource::StreamSource(iStream& Stream, TransformationFilter* AttachedTransformation)
{
    if(AttachedTransformation && Stream.m_Is.good())
    {   
        char c = Stream.m_Is.get();
        while(c != Stream.m_Delimiter && !Stream.m_Is.eof())
        {
            m_Buffer.Grow(1);
            m_Buffer[m_Buffer.Size() - 1] = c;

            c = Stream.m_Is.get();
        }

        Stream.m_Is.clear();
        
        AttachedTransformation->ProcessData(m_Buffer);
        delete AttachedTransformation;
    }
}

void StreamSink::ProcessData(SecureBlock<byte>& Data)
{
    if(m_Stream.good())
        m_Stream.write( (const char*) Data.Data(), Data.Size() );

    m_Stream.clear();
}
#pragma once

#include "pipeline/TransformationFilter.h"
#include "lockdownssl/HashFunction.h"

namespace LockdownSSL::Pipeline
{
    class HashTransformation : public TransformationFilter
    {
    public:
        HashTransformation(HashFunction& Hash) : m_HashFunction(Hash){}

        void ProcessData(SecureBlock<byte>& Data)
        {
            m_HashFunction.Put(Data);
            Data.AssignBlock( m_HashFunction.Digest() );
        }
    
    private:
        HashFunction& m_HashFunction;
    };
}
#pragma once

#include "pipeline/TransformationFilter.h"
#include "lockdownssl/HashFunction.h"

namespace LockdownSSL::Pipeline
{
    class HashTransformation : public TransformationFilter
    {
    public:
        HashTransformation(HashFunction& Hash) : m_HashFunction(Hash){}

        void ProcessData(SecureBlock<byte>& Data) override;
    
    private:
        HashFunction& m_HashFunction;
    };
}
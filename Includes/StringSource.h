#pragma once

#include "TransformationFilter.h"

namespace LockdownSSL
{
    class StringSource
    {
    public:

        StringSource(const byte* Data, size_t Length, TransfomationFilter* AttachedTransformation=nullptr)
        {
            SecureBlock<byte> data(Data, Length);
            
            TransfomationFilter* transformation = AttachedTransformation;
            while(transformation)
            {
                transformation->ProcessData(data);
                auto tmp = transformation->GetAttachedTransformation();

                delete transformation;
                transformation = tmp;
            }
        }

        StringSource(const char* Data, TransfomationFilter* AttachedTransformation=nullptr)
        {
            size_t len = std::strlen(Data);
            
            SecureBlock<byte> data(len);
            std::memcpy(data.Data(), Data, len * sizeof(byte));
            
            TransfomationFilter* transformation = AttachedTransformation;
            while(transformation)
            {
                transformation->ProcessData(data);
                auto tmp = transformation->GetAttachedTransformation();

                delete transformation;
                transformation = tmp;
            }
        }
    };
}
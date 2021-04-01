#pragma once

#include <string>

#include "pipeline/Source.h"

namespace LockdownSSL::Pipeline
{
    class StringSource : public Source
    {
    public:

        StringSource(const byte* Data, size_t Length);
        StringSource(const char* Data);
        StringSource(const std::string& Data) : StringSource(Data.c_str()) {}
    };
}
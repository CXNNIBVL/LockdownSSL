#pragma once

#include <istream>

#include "pipeline/Source.h"

namespace LockdownSSL::Pipeline
{
    class StreamSource : public Source
    {
    public:
        explicit StreamSource(std::istream& inStream, char Delimiter=-1);
    };
}
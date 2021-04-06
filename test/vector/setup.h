#pragma once

#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> FailList;
static void PrintFailed()
{
    std::cout << "\n***** FAILED ALGORITHMS *****\n" << std::endl;
    if(FailList.size())
    {
        for(std::string Name : FailList)
            std::cout << Name << std::endl;

        return;
    }

    std::cout << "None" << std::endl;
}

static std::string GetStatus(bool Verified, std::string Algorithm)
{
    if(Verified)
        return "Success";

    FailList.push_back(Algorithm);
    return "Failed";
}


#include "pipeline/Verification.h"
#include "pipeline/StringSource.h"
#include "pipeline/Hex.h"

using namespace LockdownSSL;
using namespace LockdownSSL::Pipeline;

static SecureBlock<byte> DecodeString(std::string String)
{
    StringSource ss(String); ss > HexDecoder();
    return ss.GetBuffer();
}

#include "lockdownssl/HashFunction.h"
#include "pipeline/HashTransformation.h"
static void VerifyHashFunction(std::string Algorithm, HashFunction& Hash, std::string InputString, std::string ExpectedString)
{
    std::cout << "Algorithm: " << Algorithm << std::endl;

    auto Input = DecodeString(InputString);
    auto Expected = DecodeString(ExpectedString);

    bool ver;
    StringSource(Input.Data(), Input.Size())
    > HashTransformation(Hash)
    > VerificationFilter(Expected, ver, false);

    std::cout << "Status: " << GetStatus(ver, Algorithm) << std::endl;
}
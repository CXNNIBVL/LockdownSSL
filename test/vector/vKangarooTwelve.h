#pragma once

#include "vector/setup.h"
#include "lockdownssl/KangarooTwelve.h"

std::string k12_test0_M = "";
std::string k12_test0_C = "";
std::string k12_test0_expected = "1a c2 d4 50 fc 3b 42 05 d1 9d a7 bf ca 1b 37 51 3c 08 03 57 7a c7 16 7f 06 fe 2c e1 f0 ef 39 e5";
size_t k12_test0_outlen = 32;

std::string k12_test1_M = "";
std::string k12_test1_C = "";
std::string k12_test1_expected = "1a c2 d4 50 fc 3b 42 05 d1 9d a7 bf ca 1b 37 51 3c 08 03 57 7a c7 16 7f 06 fe 2c e1 f0 ef 39 e5 42 69 c0 56 b8 c8 2e 48 27 60 38 b6 d2 92 96 6c c0 7a 3d 46 45 27 2e 31 ff 38 50 81 39 eb 0a 71";
size_t k12_test1_outlen = 64;

void VerifyKangarooTwelve()
{
    KangarooTwelve k12;

    k12.SetCustomisationString(k12_test0_C);
    k12.SetDigestSize(k12_test0_outlen);
    VerifyHashFunction("KangarooTwelve Test 0", k12, k12_test0_M, k12_test0_expected);

    
}
#pragma once

#include "lockdownssl/KeccakCore.h"

namespace LockdownSSL
{
    class Keccak_224 : public Keccak_P_1600
    {
    public:
        Keccak_224() : Keccak_P_1600(144, 24, 0x01, 28){}
    };

    class Keccak_256 : public Keccak_P_1600
    {
    public:
        Keccak_256() : Keccak_P_1600(136, 24, 0x01, 32){}
    };

    class Keccak_384 : public Keccak_P_1600
    {
    public:
        Keccak_384() : Keccak_P_1600(104, 24, 0x01, 48){}
    };

    class Keccak_512 : public Keccak_P_1600
    {
    public:
        Keccak_512() : Keccak_P_1600(72, 24, 0x01, 64){}
    };
}
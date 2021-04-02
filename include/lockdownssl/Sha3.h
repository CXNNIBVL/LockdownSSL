#pragma once

#include "lockdownssl/KeccakCore.h"

namespace LockdownSSL
{
    class Sha3_224 : public Keccak_P_1600
    {
    public:
        Sha3_224() : Keccak_P_1600(144, 24, 0x06, 28){}
    };

    class Sha3_256 : public Keccak_P_1600
    {
    public:
        Sha3_256() : Keccak_P_1600(136, 24, 0x06, 32){}
    };

    class Sha3_384 : public Keccak_P_1600
    {
    public:
        Sha3_384() : Keccak_P_1600(104, 24, 0x06, 48){}
    };

    class Sha3_512 : public Keccak_P_1600
    {
    public:
        Sha3_512() : Keccak_P_1600(72, 24, 0x06, 64){}
    };
}
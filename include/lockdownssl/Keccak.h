#pragma once

#include <assert.h>

#include "lockdownssl/HashFunction.h"
#include "misc/BitRotation.h"

#define KECCAK_DOMAIN 0x01
#define SHA3_DOMAIN 0x06
#define SHAKE_DOMAIN 0x1f
#define CSHAKE_DOMAIN 0x04

#include <iostream>
#include <iomanip>

namespace LockdownSSL
{
    template<typename T, size_t Rate, size_t NumRounds, byte Domain, size_t SDigest=0>
    class Keccak : HashFunction
    { 
    public:

        static_assert( 25 * sizeof(T) - Rate >= 0, "The combination of Rate and state size is not possible!");

        Keccak() : m_DigestSize(SDigest) {}

        void Digest(SecureBlock<byte>& Data) override
        {
            SecureBlock<byte> data = Data;

            Padding(data);

            KeccakAbsorb(data);
        }

        size_t DigestSize() override { return m_DigestSize; }

        size_t BlockSize() override { return Rate; }

    protected:
        explicit Keccak(size_t DigestSize) : m_DigestSize(DigestSize) {}

    private:
        size_t m_DigestSize;

        const unsigned int KECCAK_RO_RAW[5][5] =
        {
            {0, 1, 190, 28, 91},
            {36, 300, 6, 55, 276},
            {3, 10, 2, 153, 231},
            {105, 45, 15, 21, 136},
            {210, 66, 253, 120, 78},
        };

        const word64 KECCAK_RC_RAW[24] =
        {
            0x0000000000000001, 0x0000000000008082, 0x800000000000808A, 0x8000000080008000, 0x000000000000808B, 0x0000000080000001,
            0x8000000080008081, 0x8000000000008009, 0x000000000000008A, 0x0000000000000088, 0x0000000080008009, 0x000000008000000A,
            0x000000008000808B, 0x800000000000008B, 0x8000000000008089, 0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
            0x000000000000800A, 0x800000008000000A, 0x8000000080008081, 0x8000000000008080, 0x0000000080000001, 0x8000000080008008,
        };

        inline word64 RoundConstant(int round)
        {
            return ( KECCAK_RC_RAW[round] & ( 0xFFFFFFFFFFFFFFFF >> 8 * ( sizeof(word64) - sizeof(T) ) ) );
        }

        inline byte RotationOffset(int y, int x)
        {
            return KECCAK_RO_RAW[y][x] % ( 8 * sizeof(T) );
        }

        void Padding(SecureBlock<byte>& data)
        {
            size_t initialSize = data.Size();

            size_t size_padding = Rate - ( ( initialSize + 1 ) % Rate);

            data.CleanGrow(size_padding + 1);

            data[initialSize] = Domain;

            data[data.Size() - 1] ^= 0x80;
        }

        T StateVal(byte* ptr)
        {
            T state_val = 0;

            for(int i = sizeof(T) - 1; i >= 0; i--)
                state_val = ( state_val << 8) | ptr[i];

            return state_val;
        }

        void KeccakAbsorb(SecureBlock<byte>& data)
        {
            T state[5][5] = 
            {
                {0,0,0,0,0},
                {0,0,0,0,0},
                {0,0,0,0,0},
                {0,0,0,0,0},
                {0,0,0,0,0},
            };

            size_t num_parts = data.Size() / Rate;
            
            for(size_t p = 0; p < num_parts; p++)
            {
                byte x = 0, y = 0, rate_ctr = 0;

                while(rate_ctr < Rate)
                {
                    state[y][x++] ^= StateVal(data.Data() + rate_ctr + p * Rate);
                    
                    rate_ctr += sizeof(T);

                    if(x == 5)
                    {
                        x = 0;
                        y++;
                    }
                }
                
                Keccak_P(state);
            }
        }

        void Theta(T(&state)[5][5])
        {
            T C[5];
            T D[5];

            for (int x = 0; x < 5; x++)
            {
                C[x] = (state[0][x]) ^ (state[1][x]) ^ (state[2][x]) ^ (state[3][x]) ^ (state[4][x]);
            }

            for (int x = 0; x < 5; x++)
            {
                D[x] = ( C[ ( x + 4 ) % 5 ] ) ^ rotl<T>(C[ ( x + 1 ) % 5 ], 1);
            }

            for (int x = 0; x < 5; x++)
            {
                for (int y = 0; y < 5; y++)
                {
                    state[y][x] ^= D[x];
                }
            }

            printState(state, "Theta");
        }

        void Rho_Pi_Chi(T(&state)[5][5])
        {
            T B[5][5];

            for (int x = 0; x < 5; x++)
            {
                for (int y = 0; y < 5; y++)
                {
                    B[y][(2 * x + 3 * y) % 5] = rotl( state[y][x], RotationOffset(y,x) );
                }
            }

            printState(B, "Rho"); //Hier Data alignment falsch

            for (int x = 0; x < 5; x++)
            {
                for (int y = 0; y < 5; y++)
                {
                    state[y][x] = B[y][x] ^ ( ~( B[y][ ( x + 1 ) % 5] ) & ( B[y][ ( x + 2 ) % 5] ) );
                }
            }

            printState(state, "Pi-Chi");
        }

        void Iota(T(&state)[5][5], int iteration)
        {
            state[0][0] ^= RoundConstant(iteration);

            printState(state, "Iota");
        }

        void printState(word64(&state)[5][5], const char* id)
        {
            printf("\n\n***** %s *****\n\n", id);

            byte b[8];

            int iter = 0;
            for(int y = 0; y < 5; y++)
            {
                for(int x = 0; x < 5; x ++)
                {
                    word64 tmp = state[y][x];

                    b[0] = (byte) tmp & 0x00000000000000FF;
                    b[1] = (byte) ((tmp & 0x000000000000FF00)>> 8);
                    b[2] = (byte) ((tmp & 0x0000000000FF0000) >> 16);
                    b[3] = (byte) ((tmp & 0x00000000FF000000) >> 24);
                    b[4] = (byte) ((tmp & 0x000000FF00000000) >> 32);
                    b[5] = (byte) ((tmp & 0x0000FF0000000000) >> 40);
                    b[6] = (byte) ((tmp & 0x00FF000000000000) >> 48);
                    b[7] = (byte) ((tmp & 0xFF00000000000000) >> 56);

                    for(int i = 0; i< 8; i++)
                        printf("%02X ", b[i]);
                    
                    iter++;
                    if(iter == 2)
                    {
                        iter = 0;
                        printf("\n");
                    }
                }
            }
        }

        void Keccak_P(T(&state)[5][5])
        {
            for(int i = 24 - NumRounds; i < 24; i++)
            {
                printf("\n\n===== ROUND %d =====\n\n", i);

                Theta(state);
                Rho_Pi_Chi(state);
                Iota(state, i);

                // std::cout << "--------- ROUND " << i << " ---------\n" << std::endl;

                // for(int y = 0; y < 5; y++)
                // {
                //     for(int x = 0; x < 5; x++)
                //     {
                //         std::cout << y << "," << x << "\t" << std::hex << state[y][x] << std::endl;
                //     }
                // }
            }
        }
    };


    //Keccak Base types
    template<size_t Rate, size_t NumRounds, byte Domain, size_t SDigest=0>
    using Keccak_P_1600 = Keccak<word64, Rate, NumRounds, Domain, SDigest>;

    template<size_t Rate, size_t NumRounds, byte Domain, size_t SDigest=0>
    using Keccak_P_800 = Keccak<word32, Rate, NumRounds, Domain, SDigest>;

    template<size_t Rate, size_t NumRounds, byte Domain, size_t SDigest=0>
    using Keccak_P_400 = Keccak<word16, Rate, NumRounds, Domain, SDigest>;

    template<size_t Rate, size_t NumRounds, byte Domain, size_t SDigest=0>
    using Keccak_P_200 = Keccak<byte, Rate, NumRounds, Domain, SDigest>;

    //Standard types
    typedef Keccak_P_1600<144, 24, SHA3_DOMAIN, 28> Sha3_224;
    typedef Keccak_P_1600<136, 24, SHA3_DOMAIN, 32> Sha3_256;
    typedef Keccak_P_1600<104, 24, SHA3_DOMAIN, 48> Sha3_384;
    typedef Keccak_P_1600<72, 24, SHA3_DOMAIN, 64> Sha3_512;

    typedef Keccak_P_1600<144, 24, KECCAK_DOMAIN, 28> Keccak_224;
    typedef Keccak_P_1600<136, 24, KECCAK_DOMAIN, 32> Keccak_256;
    typedef Keccak_P_1600<104, 24, KECCAK_DOMAIN, 48> Keccak_384;
    typedef Keccak_P_1600<72, 24, KECCAK_DOMAIN, 64> Keccak_512;

    class Shake_128 : Keccak_P_1600<168, 24, SHAKE_DOMAIN>
    {
    public:
        Shake_128(size_t OutputSize) : Keccak(OutputSize) {}
    };

    class Shake_256 : Keccak_P_1600<136, 24, SHAKE_DOMAIN>
    {
    public:
        Shake_256(size_t OutputSize) : Keccak(OutputSize) {}
    };
}

#undef KECCAK_DOMAIN
#undef SHA3_DOMAIN
#undef SHAKE_DOMAIN
#undef CSHAKE_DOMAIN
#include "Sha3.h"

const unsigned int KECCAK_RO[5][5] =
{
	{0,1,62,28,27},
	{36,44,6,55,20},
	{3,10,43,25,39},
	{41,45,15,21,8},
	{18,2,61,56,14},
};

const word64 KECCAK_RC[24] =
{
	0x0000000000000001,
	0x0000000000008082,
	0x800000000000808A,
	0x8000000080008000,
	0x000000000000808B,
	0x0000000080000001,
	0x8000000080008081,
	0x8000000000008009,
	0x000000000000008A,
	0x0000000000000088,
	0x0000000080008009,
	0x000000008000000A,
	0x000000008000808B,
	0x800000000000008B,
	0x8000000000008089,
	0x8000000000008003,
	0x8000000000008002,
	0x8000000000000080,
	0x000000000000800A,
	0x800000008000000A,
	0x8000000080008081,
	0x8000000000008080,
	0x0000000080000001,
	0x8000000080008008,
};

const int Sha3_delim = 0x06;
const int Shake_delim = 0x1f;

#define LANESIZE 64
#define ROW_COL_SIZE 5
#define MOD_ADD % ROW_COL_SIZE
#define MOD_LANESIZE % LANESIZE

static inline word64 left_rot(word64 value, unsigned int count)
{
	return (value << count) | (value >> (64 - count));
}

void theta(word64(&state)[5][5])
{
	word64 C[5];
	word64 D[5];

	for (int a = 0; a < 5; a++)
	{
		C[a] = (state[0][a]) ^ (state[1][a]) ^ (state[2][a]) ^ (state[3][a]) ^ (state[4][a]);
	}

	for (int i = 0; i < 5; i++)
	{
		word64 p2 = (left_rot(C[(i + 1) MOD_ADD], 1 MOD_LANESIZE));
		D[i] = (C[(i + 4) MOD_ADD]) ^ p2;
	}

	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			state[y][x] ^= D[x];
		}
	}
}

#include <iostream>
#include <iomanip>

void rho_pi_chi(word64(&state)[5][5])
{
	word64 B[5][5];

	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			B[(2 * x + 3 * y) MOD_ADD][y] = left_rot(state[y][x], (KECCAK_RO[y][x] MOD_LANESIZE));
		}
	}

	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			state[y][x] = B[y][x] ^ (~(B[y][(x + 1) MOD_ADD]) & (B[y][(x + 2) MOD_ADD]));
		}
	}
}

void iota(word64(&state)[5][5], int iteration)
{
	state[0][0] ^= KECCAK_RC[iteration];
	std::cout << std::hex << KECCAK_RC[iteration] << std::endl;
}

byte* extract_from_state(word64(&state)[5][5])
{
	byte* u8_state = new byte[200];
	byte lane[8];

	long yctr = 0;
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			word64 tmp = state[x][y];

			lane[7] = (tmp & 0xFF00000000000000) >> 56;
			lane[6] = (tmp & 0x00FF000000000000) >> 48;
			lane[5] = (tmp & 0x0000FF0000000000) >> 40;
			lane[4] = (tmp & 0x000000FF00000000) >> 32;
			lane[3] = (tmp & 0x00000000FF000000) >> 24;
			lane[2] = (tmp & 0x0000000000FF0000) >> 16;
			lane[1] = (tmp & 0x000000000000FF00) >> 8;
			lane[0] = tmp & 0x00000000000000FF;

			for (int i = 0; i < 8; i++) {
				u8_state[yctr++] = lane[i];
			}
		}
	}

	return u8_state;
}

std::vector<word64> pre_processing(std::vector<byte>& data, int rate, int delimiter)
{
	word32 initialSize = data.size();

	word32 size_padding = rate - ((initialSize + 1) % rate);

	data.resize(initialSize + size_padding + 1);

	data[initialSize] = delimiter;

	data[data.size() - 1] ^= 0x80;

	word32 parsed_size = data.size() / 8;

	auto parsed_data = std::vector<word64>(parsed_size);

	for (word32 i = 0; i < parsed_size; i++)
	{
		parsed_data[i] = (word64)(data[(i * 8) + 7]) << 56 |
			(word64)(data[(i * 8) + 6]) << 48 |
			(word64)(data[(i * 8) + 5]) << 40 |
			(word64)(data[(i * 8) + 4]) << 32 |
			(word64)(data[(i * 8) + 3]) << 24 |
			(word64)(data[(i * 8) + 2]) << 16 |
			(word64)(data[(i * 8) + 1]) << 8 |
			(word64)(data[(i * 8)]);
	}

	return parsed_data;
}

void keccak_f(word64(&state)[5][5])
{
	for (int i = 0; i < 24; i++)
	{
		theta(state);
		rho_pi_chi(state);
		iota(state, i);
	}
}

std::vector<byte> squeeze(word64(&state)[5][5], word64 out_len, int rate)
{
	auto output = std::vector<byte>(out_len);

	if (out_len > 0 && out_len <= rate)
	{
		byte* ex_b = extract_from_state(state);

		for (word32 i = 0; i < out_len; i++)
		{
			output[i] = ex_b[i];
		}

		delete[] ex_b;
	}
	else if (out_len > rate)
	{
		word32 out_ctr = 0;

		byte* ex_b = extract_from_state(state);

		for (int i = 0; i < rate; i++)
		{
			output[i] = ex_b[i];
		}

		delete[] ex_b;

		out_ctr = rate;

		while (out_ctr != out_len)
		{
			keccak_f(state);

			ex_b = extract_from_state(state);

			for (int i = 0; i < rate && out_ctr < out_len; i++)
			{
				output[out_ctr++] = ex_b[i];
			}

			delete[] ex_b;
		}
	}

	return output;
}

std::vector<byte> keccakInternal_run(std::vector<word64> parsed_data, word64 r_64, int rate, word64 out_len)
{
	word64 state[5][5] =
	{
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0}
	};

	word32 num_parts = parsed_data.size() / r_64;
	word64 rate_ctr;

	for (long i = 0; i < num_parts; i++)
	{
		rate_ctr = 0;
		for (int x = 0; x < 5; x++)
		{
			for (int y = 0; y < 5; y++)
			{
				state[x][y] ^= rate_ctr == r_64 ? 0 : parsed_data[(i * r_64) + rate_ctr++];
			}
		}

		keccak_f(state);
	}

	return squeeze(state, out_len, rate);
}

std::vector<byte> keccak1600_run(std::vector<byte> Data, int rate, int delimiter, word64 out_len)
{
	std::vector<byte> data = std::vector<byte>(Data.begin(), Data.end());

	word64 r_64 = rate / 8;

	return keccakInternal_run(pre_processing(data, rate, delimiter), r_64, rate, out_len);
}

using namespace LockdownSSL::Hash;

const int Sha3::getBlockSize()
{
	return blockSize;
}

std::vector<byte> Sha3::getHash(std::vector<byte>& data)
{
	return keccak1600_run(data, getBlockSize(), Sha3_delim, output_length);
}

Sha3 Sha3::getInstance_224()
{
	return Sha3(28, 144);
}

Sha3 Sha3::getInstance_256()
{
	return Sha3(32, 136);
}

Sha3 Sha3::getInstance_384()
{
	return Sha3(48, 104);
}

Sha3 Sha3::getInstance_512()
{
	return Sha3(64, 72);
}

/*-------------------------------*/

std::vector<byte> Shake::getHash(std::vector<byte>& data, const word64& outBytes, const word64& outBits)
{
	byte remainderBits = outBits > 0 && outBits < 8 ? outBits : outBits % 8;
	byte additional = remainderBits > 0 ? 1 : 0;

	word64 out_len = outBytes + ((outBits - remainderBits) / 8) + additional;

	std::vector<byte> outData = keccak1600_run(data, rate, Shake_delim, out_len);

	if (out_len != 0)
	{
		byte mask = 255 >> (8 - (remainderBits > 0 ? remainderBits : 8));
		outData[out_len - 1] &= mask;
	}

	return outData;
}

Shake Shake::getInstance_128()
{
	return Shake(168);
}

Shake Shake::getInstance_256()
{
	return Shake(136);
}

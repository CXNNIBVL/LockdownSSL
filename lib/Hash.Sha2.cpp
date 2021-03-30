#include "Sha2.h"

const word32 sha224_hBuf[] = 	{ 0xc1059ed8, 0x367cd507, 0x3070dd17, 0xf70e5939, 0xffc00b31, 0x68581511, 0x64f98fa7, 0xbefa4fa4 };
const word32 sha256_hBuf[] = 	{ 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };
const word64 sha384_hBuf[] = 		{ 0xcbbb9d5dc1059ed8, 0x629a292a367cd507, 0x9159015a3070dd17, 0x152fecd8f70e5939, 0x67332667ffc00b31, 0x8eb44a8768581511, 0xdb0c2e0d64f98fa7, 0x47b5481dbefa4fa4 };
const word64 sha512_hBuf[] = 		{ 0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1, 0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179 };
const word64 sha512_224_hBuf[] = 	{ 0x8C3D37C819544DA2, 0x73E1996689DCD4D6, 0x1DFAB7AE32FF9C82, 0x679DD514582F9FCF,0x0F6D2B697BD44DA8, 0x77E36F7304C48942, 0x3F9D85A86A1D36C8, 0x1112E6AD91D692A1 };
const word64 sha512_256_hBuf[] = 	{ 0x22312194FC2BF72C, 0x9F555FA3C84C64C2, 0x2393B86B6F53B151, 0x963877195940EABD, 0x96283EE2A88EFFE3, 0xBE5E1E2553863992, 0x2B0199FC2C85B8AA, 0x0EB72DDC81C52CA2 };

const word32 sha224_256_kBuf[] =
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

const word64 sha384_512_kBuf[] =
{
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538,
	0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe,
	0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66dfab,
	0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed,
	0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
	0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373,
	0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c,
	0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6,
	0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

#define BLOCKSIZE_32B 64
#define BLOCKSIZE_64B 128

void parse_u8_to_u32(byte* msg, word32* words)
{
	for (int i = 0, ctr = 0; i < 64; i += 4, ctr++)
		words[ctr] =  (word32)msg[i] << 24 | (word32)msg[i + 1] << 16 | (word32)msg[i + 2] << 8 | (word32)msg[i + 3];
}

void parse_u8_to_u64(byte* msg, word64* words)
{
	for (int i = 0, ctr = 0; i < 128; i += 8, ctr++)
		words[ctr] = (word64)msg[i] << 56 | (word64)msg[i + 1] << 48 | (word64)msg[i + 2] << 40 | (word64)msg[i + 3] << 32 | (word64)msg[i + 4] << 24 | (word64)msg[i + 5] << 16 | (word64)msg[i + 6] << 8 | (word64)msg[i + 7];
}

inline word32 right_rot_32(word32 value, unsigned int count)
{
	return value >> count | value << (32 - count);
}

inline word64 right_rot_64(word64 value, unsigned int count)
{
	return value >> count | value << (64 - count);
}

void padding_32b(std::vector<byte>& data)
{
	word32 initial_size = data.size();

	word32 pad_size = BLOCKSIZE_32B - ((initial_size + 9) % BLOCKSIZE_32B);

	data.resize(initial_size + pad_size + 9);
	data[initial_size] = 0x80;

	word64 length_bits = ((word64)initial_size) * 8;
	byte* length_bytes = (byte*)&length_bits;

	for (int i = initial_size + 1 + pad_size, ctr = 7; i < initial_size + pad_size + 9; i++, ctr--)
	{
		data[i] = length_bytes[ctr];
	}
}

void compress_32b(std::vector<byte>& data, word32 part, word32* h, const word32* k)
{
	byte msg[64];
	word32 w[64];

	for (int i = part * 64, ctr = 0; i < (part * 64) + 64; i++, ctr++)
	{
		msg[ctr] = data[i];
	}

	parse_u8_to_u32(msg, w);

	for (int i = 16; i < 64; i++)
	{
		word32 s0 = (right_rot_32(w[i - 15], 7)) ^ (right_rot_32(w[i - 15], 18)) ^ (w[i - 15] >> 3);
		word32 s1 = (right_rot_32(w[i - 2], 17)) ^ (right_rot_32(w[i - 2], 19)) ^ (w[i - 2] >> 10);
		w[i] = (w[i - 16] + s0 + w[i - 7] + s1) ;
	}

	word32 a = h[0];
	word32 b = h[1];
	word32 c = h[2];
	word32 d = h[3];
	word32 e = h[4];
	word32 f = h[5];
	word32 g = h[6];
	word32 h_ = h[7];

	for (int i = 0; i < 64; i++)
	{
		word32 S1 = (right_rot_32(e, 6)) ^ (right_rot_32(e, 11)) ^ (right_rot_32(e, 25));
		word32 ch = (e & f) ^ ((~e) & g);
		word32 tmp_1 = (h_ + S1 + ch + k[i] + w[i]) ;
		word32 S0 = (right_rot_32(a, 2)) ^ (right_rot_32(a, 13)) ^ (right_rot_32(a, 22));
		word32 maj = (a & b) ^ (a & c) ^ (b & c);
		word32 tmp_2 = (S0 + maj) ;

		h_ = g;
		g = f;
		f = e;
		e = (d + tmp_1) ;
		d = c;
		c = b;
		b = a;
		a = (tmp_1 + tmp_2) ;
	}

	h[0] += a;
	h[1] += b;
	h[2] += c;
	h[3] += d;
	h[4] += e;
	h[5] += f;
	h[6] += g;
	h[7] += h_;
}

std::vector<byte> extract_32b(const word32* h, int& ommit)
{
	int num_elements = 32 - ommit;
	std::vector<byte> U8_h;
	U8_h.reserve(num_elements);

	byte tmp_store[4];

	word32 ctr = 0;
	for (int i = 0; i < 8; i++)
	{
		word32 tmp = h[i];
		
		tmp_store[0] = (tmp & 0xFF000000) >> 24;
		tmp_store[1] = (tmp & 0x00FF0000) >> 16;
		tmp_store[2] = (tmp & 0x0000FF00) >> 8;
		tmp_store[3] = (tmp & 0x000000FF);

		for (int k = 0; k < 4; k++, ctr++)
		{	
			U8_h[ctr] = tmp_store[k];

			if(ctr == num_elements)
				break;
		}
	}

	return U8_h;
}

std::vector<byte> getHash_32b(std::vector<byte>& data, const word32* h, int& ommit_h)
{
	std::vector<byte> Data;
	for(int i = 0; i  < data.size(); i++)
		Data.push_back(data[i]);

	word32 h_buf[8];
	
	for(int i = 0; i < 8; i++)
		h_buf[i] = h[i];

	const word32* k = sha224_256_kBuf;

	padding_32b(Data);

	word32 num_parts = Data.size() / BLOCKSIZE_32B;

	for (word32 i = 0; i < num_parts; i++)
		compress_32b(Data, i, h_buf, k);

	return extract_32b(h_buf, ommit_h);
}

void padding_64b(std::vector<byte>& data)
{
	word32 initial_size = data.size();
	
	word32 pad_size = BLOCKSIZE_64B - ((initial_size + 17) % BLOCKSIZE_64B);

	data.resize(initial_size + pad_size + 17);
	data[initial_size] = 0x80;

	word64 length_bits = ((word64)initial_size) * 8;
	byte* length_bytes = (byte*)&length_bits;

	for (int i = initial_size + 1 + pad_size + 8, ctr = 7; i < initial_size + pad_size + 17; i++, ctr--)
	{
		data[i] = length_bytes[ctr];
	}
}

void compress_64b(std::vector<byte>& data, word32 part, word64* h, const word64* k)
{
	byte msg[128];
	word64 w[80];

	for (int i = part * 128, ctr = 0; i < (part * 128) + 128; i++, ctr++)
	{
		msg[ctr] = data[i];
	}

	parse_u8_to_u64(msg, w);

	for (int i = 16; i < 80; i++)
	{
		word64 s0 = (right_rot_64(w[i - 15], 1)) ^ (right_rot_64(w[i - 15], 8)) ^ (w[i - 15] >> 7);
		word64 s1 = (right_rot_64(w[i - 2], 19)) ^ (right_rot_64(w[i - 2], 61)) ^ (w[i - 2] >> 6);
		w[i] = (w[i - 16] + s0 + w[i - 7] + s1) ;
	}

	word64 a = h[0];
	word64 b = h[1];
	word64 c = h[2];
	word64 d = h[3];
	word64 e = h[4];
	word64 f = h[5];
	word64 g = h[6];
	word64 h_ = h[7];

	for (int i = 0; i < 80; i++)
	{
		word64 S1 = (right_rot_64(e, 14)) ^ (right_rot_64(e, 18)) ^ (right_rot_64(e, 41));
		word64 ch = (e & f) ^ ((~e) & g);
		word64 tmp_1 = (h_ + S1 + ch + k[i] + w[i]) ;
		word64 S0 = (right_rot_64(a, 28)) ^ (right_rot_64(a, 34)) ^ (right_rot_64(a, 39));
		word64 maj = (a & b) ^ (a & c) ^ (b & c);
		word64 tmp_2 = (S0 + maj) ;

		h_ = g;
		g = f;
		f = e;
		e = (d + tmp_1) ;
		d = c;
		c = b;
		b = a;
		a = (tmp_1 + tmp_2) ;
	}

	h[0] += a;
	h[1] += b;
	h[2] += c;
	h[3] += d;
	h[4] += e;
	h[5] += f;
	h[6] += g;
	h[7] += h_;
}

std::vector<byte> extract_64b(const word64* h, int ommit)
{
	int num_elements = 64 - ommit;
	std::vector<byte> U8_h = std::vector<byte>(num_elements);
	byte tmp_store[8];

	word32 ctr = 0;
	for (int i = 0; i < 8; i++)
	{
		word64 tmp = h[i];
		
		tmp_store[0] = (tmp & 0xFF00000000000000) >> 56;
		tmp_store[1] = (tmp & 0x00FF000000000000) >> 48;
		tmp_store[2] = (tmp & 0x0000FF0000000000) >> 40;
		tmp_store[3] = (tmp & 0x000000FF00000000) >> 32;
		tmp_store[4] = (tmp & 0x00000000FF000000) >> 24;
		tmp_store[5] = (tmp & 0x0000000000FF0000) >> 16;
		tmp_store[6] = (tmp & 0x000000000000FF00) >> 8;
		tmp_store[7] = (tmp & 0x00000000000000FF);

		for (int k = 0; k < 8; k++, ctr++)
		{
			U8_h[ctr] = tmp_store[k];

			if(ctr == num_elements)
				return U8_h;
		}
	}

	return U8_h;
}

std::vector<byte> getHash_64b(std::vector<byte>& data, const word64* h, int& ommit_h)
{
	auto Data = std::vector<byte>(data.begin(), data.end());

	word64 h_buf[8];
	for(int i = 0; i < 8; i++)
		h_buf[i] = h[i];

	const word64* k = sha384_512_kBuf;

	padding_64b(Data);

	word32 num_parts = Data.size() / BLOCKSIZE_64B;

	for (word32 i = 0; i < num_parts; i++)
		compress_64b(Data, i, h_buf, k);

	return extract_64b(h_buf, ommit_h);
}

using namespace LockdownSSL::Hash;

Sha2::Sha2(int Ommit_H, const word32* Hbuf_32b, int Blocksize)
{
	hbuf_32b = Hbuf_32b;
	hbuf_64b = nullptr;
	ommit_H = Ommit_H;
	blockSize = Blocksize;
}

Sha2::Sha2(int Ommit_H, const word64* Hbuf_64b, int Blocksize)
{
	hbuf_32b = nullptr;
	hbuf_64b = Hbuf_64b;
	ommit_H = Ommit_H;
	blockSize = Blocksize;
}

std::vector<byte> Sha2::getHash(std::vector<byte>& data)
{
	return blockSize == BLOCKSIZE_32B ? getHash_32b(data, hbuf_32b, ommit_H) : getHash_64b(data, hbuf_64b, ommit_H);
}

const int Sha2::getBlockSize()
{
	return blockSize;
}

Sha2 Sha2::getInstance_224()
{
	return Sha2(4, sha224_hBuf, BLOCKSIZE_32B);
}

Sha2 Sha2::getInstance_256()
{
	return Sha2(0, sha256_hBuf, BLOCKSIZE_32B);
}

Sha2 Sha2::getInstance_384()
{
	return Sha2(16, sha384_hBuf, BLOCKSIZE_64B);
}

Sha2 Sha2::getInstance_512()
{
	return Sha2(0, sha512_hBuf, BLOCKSIZE_64B);
}

Sha2 Sha2::getInstance_512_224()
{
	return Sha2(36, sha512_224_hBuf, BLOCKSIZE_64B);
}

Sha2 Sha2::getInstance_512_256()
{
	return Sha2(32, sha512_256_hBuf, BLOCKSIZE_64B);
}
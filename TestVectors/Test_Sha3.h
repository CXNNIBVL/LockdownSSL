#ifndef LOCKDOWNSSL_SHA3_TEST
#define LOCKDOWNSSL_SHA3_TEST

#include <iostream>
#include "Sha3.h"

namespace LockdownSSL
{
	namespace Test
	{
		void sha3_224_test()
		{
			auto instance = LockdownSSL::Hash::Sha3::getInstance_224();

			auto data_1 = std::vector<byte>(0);

			std::vector<byte> out_1
			{
				0x6B,0x4E,0x03,0x42,0x36,0x67,
				0xDB,0xB7,0x3B,0x6E,0x15,0x45,
				0x4F,0x0E,0xB1,0xAB,0xD4,0x59,
				0x7F,0x9A,0x1B,0x07,0x8E,0x3F,
				0x5B,0x5A,0x6B,0xC7,

			};

			std::vector<byte> data_2{ 'a','a','a' };
			std::vector<byte> out_2
			{
				0xa9,0x9a,0x78,0x8a,0xc9,0x5c,0xc8,
				0xb7,0x78,0x41,0x28,0x68,0x8d,0xcd,
				0xf8,0x02,0x2f,0x09,0x24,0x2a,0x15,
				0xca,0xcd,0x13,0x1a,0xee,0xcd,0xb4,
			};

			auto res_1 = instance.getHash(data_1);
			for (word32 i = 0; i < out_1.size(); i++)
			{
				if (out_1[i] != res_1[i])
				{
					std::cout << "Sha3 224 Test 1 failed at index " << i << std::endl;
					std::cin.get();
				}
			}
			std::cout << "Sha3 224 Test 1 Passed" << std::endl;

			auto res_2 = instance.getHash(data_2);
			for (word32 i = 0; i < out_2.size(); i++)
			{
				if (out_2[i] != res_2[i])
				{
					std::cout << "Sha3 224 Test 2 failed at index " << i << std::endl;
					std::cin.get();
				}
			}
			std::cout << "Sha3 224 Test 2 Passed" << std::endl;

			std::cout << "Sha3 224 working properly! - Hit Enter to continue" << std::endl;

			std::cin.get();
		}

		void sha3_256_test()
		{
			auto instance = LockdownSSL::Hash::Sha3::getInstance_256();

			auto data_1 = std::vector<byte>(0);

			std::vector<byte> out_1
			{
				0xA7,0xFF,0xC6,0xF8,0xBF,0x1E,0xD7,
				0x66,0x51,0xC1,0x47,0x56,0xA0,0x61,
				0xD6,0x62,0xF5,0x80,0xFF,0x4D,0xE4,
				0x3B,0x49,0xFA,0x82,0xD8,0x0A,0x4B,
				0x80,0xF8,0x43,0x4A,
			};

			std::vector<byte> data_2{ 'a','a','a' };
			std::vector<byte> out_2
			{
				0x80,0xfb,0x34,0xa2,0xc6,0xbc,
				0x53,0x7d,0x2d,0x04,0x4c,0x01,
				0x30,0x42,0xb3,0xb3,0x62,0x39,
				0xaa,0xf3,0xcf,0xd3,0x81,0xd6,
				0x2a,0x9a,0xb8,0xe8,0x75,0x38,
				0x76,0xd0,
			};

			auto res_1 = instance.getHash(data_1);
			for (word32 i = 0; i < out_1.size(); i++)
			{
				if (out_1[i] != res_1[i])
				{
					std::cout << "Sha3 256 Test 1 failed at index " << i << std::endl;
					std::cin.get();
				}
			}
			std::cout << "Sha3 256 Test 1 Passed" << std::endl;

			auto res_2 = instance.getHash(data_2);
			for (word32 i = 0; i < out_2.size(); i++)
			{
				if (out_2[i] != res_2[i])
				{
					std::cout << "Sha3 256 Test 2 failed at index " << i << std::endl;
					std::cin.get();
				}
			}
			std::cout << "Sha3 256 Test 2 Passed" << std::endl;

			std::cout << "Sha3 256 working properly! - Hit Enter to continue" << std::endl;

			std::cin.get();
		}

		void sha3_384_test()
		{
			auto instance = LockdownSSL::Hash::Sha3::getInstance_384();

			auto data_1 = std::vector<byte>(0);

			std::vector<byte> out_1
			{
				0x0C,0x63,0xA7,0x5B,0x84,0x5E,0x4F,
				0x7D,0x01,0x10,0x7D,0x85,0x2E,0x4C,
				0x24,0x85,0xC5,0x1A,0x50,0xAA,0xAA,
				0x94,0xFC,0x61,0x99,0x5E,0x71,0xBB,
				0xEE,0x98,0x3A,0x2A,0xC3,0x71,0x38,
				0x31,0x26,0x4A,0xDB,0x47,0xFB,0x6B,
				0xD1,0xE0,0x58,0xD5,0xF0,0x04,
			};

			std::vector<byte> data_2{ 'a','a','a' };
			std::vector<byte> out_2
			{
				0xe4,0xa9,0xe9,0x1e,0x5c,0x0d,0xce,
				0x64,0x64,0x9f,0xff,0x8e,0xfa,0xb7,
				0x19,0x39,0xd2,0xb9,0xe5,0xa7,0x67,
				0x8e,0xdf,0xfd,0x19,0xe4,0x81,0x12,
				0xa7,0x44,0xe2,0xfb,0xd3,0x18,0x84,
				0xb3,0x7d,0xe3,0x4a,0x7f,0xc4,0x17,
				0x39,0xc3,0x38,0xee,0x25,0xb1,
			};

			auto res_1 = instance.getHash(data_1);
			for (word32 i = 0; i < out_1.size(); i++)
			{
				if (out_1[i] != res_1[i])
				{
					std::cout << "Sha3 384 Test 1 failed at index " << i << std::endl;
					std::cin.get();
				}
			}
			std::cout << "Sha3 384 Test 1 Passed" << std::endl;

			auto res_2 = instance.getHash(data_2);
			for (word32 i = 0; i < out_2.size(); i++)
			{
				if (out_2[i] != res_2[i])
				{
					std::cout << "Sha3 384 Test 2 failed at index " << i << std::endl;
					std::cin.get();
				}
			}
			std::cout << "Sha3 384 Test 2 Passed" << std::endl;

			std::cout << "Sha3 384 working properly! - Hit Enter to continue" << std::endl;

			std::cin.get();
		}

		void sha3_512_test()
		{
			auto instance = LockdownSSL::Hash::Sha3::getInstance_512();

			auto data_1 = std::vector<byte>(0);

			std::vector<byte> out_1
			{
				0xA6,0x9F,0x73,0xCC,0xA2,0x3A,0x9A,
				0xC5,0xC8,0xB5,0x67,0xDC,0x18,0x5A,
				0x75,0x6E,0x97,0xC9,0x82,0x16,0x4F,
				0xE2,0x58,0x59,0xE0,0xD1,0xDC,0xC1,
				0x47,0x5C,0x80,0xA6,0x15,0xB2,0x12,
				0x3A,0xF1,0xF5,0xF9,0x4C,0x11,0xE3,
				0xE9,0x40,0x2C,0x3A,0xC5,0x58,0xF5,
				0x00,0x19,0x9D,0x95,0xB6,0xD3,0xE3,
				0x01,0x75,0x85,0x86,0x28,0x1D,0xCD,
				0x26,
			};

			std::vector<byte> data_2{ 'a','a','a' };
			std::vector<byte> out_2
			{
				0xf6,0x51,0x87,0x19,0xca,0xba,0xf6,
				0x26,0x8c,0x00,0x8e,0xcc,0xa3,0xf3,
				0x9c,0x16,0x67,0x20,0xd2,0x52,0xb9,
				0xb5,0x05,0x3a,0x8b,0x37,0xa7,0xf4,
				0x04,0x65,0x22,0x2f,0xd8,0x48,0x5e,
				0x12,0x2e,0x27,0xeb,0x38,0x78,0x94,
				0xf5,0x2b,0x91,0x3d,0x7a,0xa0,0xa3,
				0xb6,0x15,0xfb,0xd6,0x2f,0xff,0x57,
				0x3d,0xbd,0xf3,0xba,0x38,0x1c,0x7e,
				0xf2,
			};

			auto res_1 = instance.getHash(data_1);
			for (word32 i = 0; i < out_1.size(); i++)
			{
				if (out_1[i] != res_1[i])
				{
					std::cout << "Sha3 512 Test 1 failed at index " << i << std::endl;
					std::cin.get();
				}
			}
			std::cout << "Sha3 512 Test 1 Passed" << std::endl;

			auto res_2 = instance.getHash(data_2);
			for (word32 i = 0; i < out_2.size(); i++)
			{
				if (out_2[i] != res_2[i])
				{
					std::cout << "Sha3 512 Test 2 failed at index " << i << std::endl;
					std::cin.get();
				}
			}
			std::cout << "Sha3 512 Test 2 Passed" << std::endl;

			std::cout << "Sha3 512 working properly! - Hit Enter to continue" << std::endl;

			std::cin.get();
		}

		void shake128_test()
		{
			auto instance = LockdownSSL::Hash::Shake::getInstance_128();

			auto data = std::vector<byte>(0);

			std::vector<byte> out_1
			{
				0x7F,0x9C,0x2B,0xA4,0xE8,
				0x8F,0x82,0x7D,0x61,0x60,
				0x45,0x50,0x76,0x05,0x85,
				0x3E,0xD7,0x3B,0x80,0x93,
				0xF6,0xEF,0xBC,0x88,0xEB,
				0x1A,0x6E,0xAC,0xFA,0x66,
				0xEF,0x26,0x3C,0xB1,0xEE,
				0xA9,0x88,0x00,0x4B,0x93,
				0x10,0x3C,0xFB,0x0A,0xEE,
				0xFD,0x2A,0x68,0x6E,0x01,
				0xFA,0x4A,0x58,0xE8,0xA3,
				0x63,0x9C,0xA8,0xA1,0xE3,
				0xF9,0xAE,0x57,0xE2,0x35,
				0xB8,0xCC,0x87,0x3C,0x23,
				0xDC,0x62,0xB8,0xD2,0x60,
				0x16,0x9A,0xFA,0x2F,0x75,
				0xAB,0x91,0x6A,0x58,0xD9,
				0x74,0x91,0x88,0x35,0xD2,
				0x5E,0x6A,0x43,0x50,0x85,
				0xB2,0xBA,0xDF,0xD6,0xDF,
				0xAA,0xC3,0x59,0xA5,0xEF,
				0xBB,0x7B,0xCC,0x4B,0x59,
				0xD5,0x38,0xDF,0x9A,0x04,
				0x30,0x2E,0x10,0xC8,0xBC,
				0x1C,0xBF,0x1A,0x0B,0x3A,
				0x51,0x20,0xEA,0x17,0xCD,
				0xA7,0xCF,0xAD,0x76,0x5F,
				0x56,0x23,0x47,0x4D,0x36,
				0x8C,0xCC,0xA8,0xAF,0x00,
				0x07,0xCD,0x9F,0x5E,0x4C,
				0x84,0x9F,0x16,0x7A,0x58,
				0x0B,0x14,0xAA,0xBD,0xEF,
				0xAE,0xE7,0xEE,0xF4,0x7C,
				0xB0,0xFC,0xA9,0x76,0x7B,
				0xE1,0xFD,0xA6,0x94,0x19,
				0xDF,0xB9,0x27,0xE9,0xDF,
				0x07,0x34,0x8B,0x19,0x66,
				0x91,0xAB,0xAE,0xB5,0x80,
				0xB3,0x2D,0xEF,0x58,0x53,
				0x8B,0x8D,0x23,0xF8,0x77,
				0x32,0xEA,0x63,0xB0,0x2B,
				0x4F,0xA0,0xF4,0x87,0x33,
				0x60,0xE2,0x84,0x19,0x28,
				0xCD,0x60,0xDD,0x4C,0xEE,
				0x8C,0xC0,0xD4,0xC9,0x22,
				0xA9,0x61,0x88,0xD0,0x32,
				0x67,0x5C,0x8A,0xC8,0x50,
				0x93,0x3C,0x7A,0xFF,0x15,
				0x33,0xB9,0x4C,0x83,0x4A,
				0xDB,0xB6,0x9C,0x61,0x15,
				0xBA,0xD4,0x69,0x2D,0x86,
				0x19,0xF9,0x0B,0x0C,0xDF,
				0x8A,0x7B,0x9C,0x26,0x40,
				0x29,0xAC,0x18,0x5B,0x70,
				0xB8,0x3F,0x28,0x01,0xF2,
				0xF4,0xB3,0xF7,0x0C,0x59,
				0x3E,0xA3,0xAE,0xEB,0x61,
				0x3A,0x7F,0x1B,0x1D,0xE3,
				0x3F,0xD7,0x50,0x81,0xF5,
				0x92,0x30,0x5F,0x2E,0x45,
				0x26,0xED,0xC0,0x96,0x31,
				0xB1,0x09,0x58,0xF4,0x64,
				0xD8,0x89,0xF3,0x1B,0xA0,
				0x10,0x25,0x0F,0xDA,0x7F,
				0x13,0x68,0xEC,0x29,0x67,
				0xFC,0x84,0xEF,0x2A,0xE9,
				0xAF,0xF2,0x68,0xE0,0xB1,
				0x70,0x0A,0xFF,0xC6,0x82,
				0x0B,0x52,0x3A,0x3D,0x91,
				0x71,0x35,0xF2,0xDF,0xF2,
				0xEE,0x06,0xBF,0xE7,0x2B,
				0x31,0x24,0x72,0x1D,0x4A,
				0x26,0xC0,0x4E,0x53,0xA7,
				0x5E,0x30,0xE7,0x3A,0x7A,
				0x9C,0x4A,0x95,0xD9,0x1C,
				0x55,0xD4,0x95,0xE9,0xF5,
				0x1D,0xD0,0xB5,0xE9,0xD8,
				0x3C,0x6D,0x5E,0x8C,0xE8,
				0x03,0xAA,0x62,0xB8,0xD6,
				0x54,0xDB,0x53,0xD0,0x9B,
				0x8D,0xCF,0xF2,0x73,0xCD,
				0xFE,0xB5,0x73,0xFA,0xD8,
				0xBC,0xD4,0x55,0x78,0xBE,
				0xC2,0xE7,0x70,0xD0,0x1E,
				0xFD,0xE8,0x6E,0x72,0x1A,
				0x3F,0x7C,0x6C,0xCE,0x27,
				0x5D,0xAB,0xE6,0xE2,0x14,
				0x3F,0x1A,0xF1,0x8D,0xA7,
				0xEF,0xDD,0xC4,0xC7,0xB7,
				0x0B,0x5E,0x34,0x5D,0xB9,
				0x3C,0xC9,0x36,0xBE,0xA3,
				0x23,0x49,0x1C,0xCB,0x38,
				0xA3,0x88,0xF5,0x46,0xA9,
				0xFF,0x00,0xDD,0x4E,0x13,
				0x00,0xB9,0xB2,0x15,0x3D,
				0x20,0x41,0xD2,0x05,0xB4,
				0x43,0xE4,0x1B,0x45,0xA6,
				0x53,0xF2,0xA5,0xC4,0x49,
				0x2C,0x1A,0xDD,0x54,0x45,
				0x12,0xDD,0xA2,0x52,0x98,
				0x33,0x46,0x2B,0x71,0xA4,
				0x1A,0x45,0xBE,0x97,0x29,
				0x0B,0x6F,
			};

			std::vector<byte> out_2 =
			{
				0x7F,0x9C,0x2B,0xA4,0xE8,0x8F,0x82,0x7D,0x61,0x60,
				0x45,0x50,0x76,0x05,0x85,0x3E,0xD7,0x3B,0x80,0x93,
				0xF6,0xEF,0xBC,0x88,0xEB,0x1A,0x6E,0xAC,0xFA,0x66,
				0xEF,0x26,0x3C,0xB1,0xEE,0xA9,0x88,0x00,0x4B,0x93,
				0x10,0x3C,0xFB,0x0A,0xEE,0xFD,0x2A,0x68,0x6E,0x01,
				0xFA,0x4A,0x58,0xE8,0xA3,0x63,0x9C,0xA8,0xA1,0xE3,
				0xF9,0xAE,0x57,0xE2,0x35,0xB8,0xCC,0x87,0x3C,0x23,
				0xDC,0x62,0xB8,0xD2,0x60,0x16,0x9A,0xFA,0x2F,0x75,
				0xAB,0x91,0x6A,0x58,0xD9,0x74,0x91,0x88,0x35,0xD2,
				0x5E,0x6A,0x43,0x50,0x85,0xB2,0xBA,0xDF,0xD6,0xDF,
				0xAA,0xC3,0x59,0xA5,0xEF,0xBB,0x7B,0xCC,0x4B,0x59,
				0xD5,0x38,0xDF,0x9A,0x04,0x30,0x2E,0x10,0xC8,0xBC,
				0x1C,0xBF,0x1A,0x0B,0x3A,0x51,0x20,0xEA,0x17,0xCD,
				0xA7,0xCF,0xAD,0x76,0x5F,0x56,0x23,0x47,0x4D,0x36,
				0x8C,0xCC,0xA8,0xAF,0x00,0x07,0xCD,0x9F,0x5E,0x4C,
				0x84,0x9F,0x16,0x7A,0x58,0x0B,0x14,0xAA,0xBD,0xEF,
				0xAE,0xE7,0xEE,0xF4,0x7C,0xB0,0xFC,0xA9,0x76,0x7B,
				0xE1,0xFD,0xA6,0x94,0x19,0xDF,0xB9,0x27,0xE9,0xDF,
				0x07,0x34,0x8B,0x19,0x66,0x91,0xAB,0xAE,0xB5,0x80,
				0xB3,0x2D,0xEF,0x58,0x53,0x8B,0x8D,0x23,0xF8,0x77,
				0x32,0xEA,0x63,0xB0,0x2B,0x4F,0xA0,0xF4,0x87,0x33,
				0x60,0xE2,0x84,0x19,0x28,0xCD,0x60,0xDD,0x4C,0xEE,
				0x8C,0xC0,0xD4,0xC9,0x22,0xA9,0x61,0x88,0xD0,0x32,
				0x67,0x5C,0x8A,0xC8,0x50,0x93,0x3C,0x7A,0xFF,0x15,
				0x33,0xB9,0x4C,0x83,0x4A,0xDB,0xB6,0x9C,0x61,0x15,
				0xBA,0xD4,0x69,0x2D,0x86,0x19,0xF9,0x0B,0x0C,0xDF,
				0x8A,0x7B,0x9C,0x26,0x40,0x29,0xAC,0x18,0x5B,0x70,
				0xB8,0x3F,0x28,0x01,0xF2,0xF4,0xB3,0xF7,0x0C,0x59,
				0x3E,0xA3,0xAE,0xEB,0x61,0x3A,0x7F,0x1B,0x1D,0xE3,
				0x3F,0xD7,0x50,0x81,0xF5,0x92,0x30,0x5F,0x2E,0x45,
				0x26,0xED,0xC0,0x96,0x31,0xB1,0x09,0x58,0xF4,0x64,
				0xD8,0x89,0xF3,0x1B,0xA0,0x10,0x25,0x0F,0xDA,0x7F,
				0x13,0x68,0xEC,0x29,0x67,0xFC,0x84,0xEF,0x2A,0xE9,
				0xAF,0xF2,0x68,0xE0,0xB1,0x70,0x0A,0xFF,0xC6,0x82,
				0x0B,0x52,0x3A,0x3D,0x91,0x71,0x35,0xF2,0xDF,0xF2,
				0xEE,0x06,0xBF,0xE7,0x2B,0x31,0x24,0x72,0x1D,0x4A,
				0x26,0xC0,0x4E,0x53,0xA7,0x5E,0x30,0xE7,0x3A,0x7A,
				0x9C,0x4A,0x95,0xD9,0x1C,0x55,0xD4,0x95,0xE9,0xF5,
				0x1D,0xD0,0xB5,0xE9,0xD8,0x3C,0x6D,0x5E,0x8C,0xE8,
				0x03,0xAA,0x62,0xB8,0xD6,0x54,0xDB,0x53,0xD0,0x9B,
				0x8D,0xCF,0xF2,0x73,0xCD,0xFE,0xB5,0x73,0xFA,0xD8,
				0xBC,0xD4,0x55,0x78,0xBE,0xC2,0xE7,0x70,0xD0,0x1E,
				0xFD,0xE8,0x6E,0x72,0x1A,0x3F,0x7C,0x6C,0xCE,0x27,
				0x5D,0xAB,0xE6,0xE2,0x14,0x3F,0x1A,0xF1,0x8D,0xA7,
				0xEF,0xDD,0xC4,0xC7,0xB7,0x0B,0x5E,0x34,0x5D,0xB9,
				0x3C,0xC9,0x36,0xBE,0xA3,0x23,0x49,0x1C,0xCB,0x38,
				0xA3,0x88,0xF5,0x46,0xA9,0xFF,0x00,0xDD,0x4E,0x13,
				0x00,0xB9,0xB2,0x15,0x3D,0x20,0x41,0xD2,0x05,0xB4,
				0x43,0xE4,0x1B,0x45,0xA6,0x53,0xF2,0xA5,0xC4,0x49,
				0x2C,0x1A,0xDD,0x54,0x45,0x12,0xDD,0xA2,0x52,0x98,
				0x33,0x46,0x2B,0x71,0xA4,0x1A,0x45,0xBE,0x97,0x29,
				0x0B,0x0F,
			};

			auto res_1 = instance.getHash(data, 512, 0);
			for (word32 i = 0; i < out_1.size(); i++)
			{
				if (out_1[i] != res_1[i])
				{
					std::cout << "Shake128 Test 1 failed at index " << i << std::endl;
					std::cin.get();
				}
			}
			std::cout << "Shake128 Test 1 Passed" << std::endl;

			auto res_2 = instance.getHash(data, 0, 4093);
			for (word32 i = 0; i < out_2.size(); i++)
			{
				if (out_2[i] != res_2[i])
				{
					std::cout << "Shake128 Test 2 failed at index " << i << std::endl;
					std::cin.get();
				}
			}
			std::cout << "Shake128 Test 2 Passed" << std::endl;

			std::cout << "Shake128 working properly! - Hit Enter to continue" << std::endl;

			std::cin.get();
		}

		void shake256_test()
		{
			auto instance = LockdownSSL::Hash::Shake::getInstance_256();

			auto data = std::vector<byte>(0);

			std::vector<byte> out
			{
				0x46,0xB9,0xDD,0x2B,0x0B,0xA8,0x8D,0x13,0x23,0x3B,0x3F,0xEB,
				0x74,0x3E,0xEB,0x24,0x3F,0xCD,0x52,0xEA,0x62,0xB8,0x1B,0x82,
				0xB5,0x0C,0x27,0x64,0x6E,0xD5,0x76,0x2F,0xD7,0x5D,0xC4,0xDD,
				0xD8,0xC0,0xF2,0x00,0xCB,0x05,0x01,0x9D,0x67,0xB5,0x92,0xF6,
				0xFC,0x82,0x1C,0x49,0x47,0x9A,0xB4,0x86,0x40,0x29,0x2E,0xAC,
				0xB3,0xB7,0xC4,0xBE,0x14,0x1E,0x96,0x61,0x6F,0xB1,0x39,0x57,
				0x69,0x2C,0xC7,0xED,0xD0,0xB4,0x5A,0xE3,0xDC,0x07,0x22,0x3C,
				0x8E,0x92,0x93,0x7B,0xEF,0x84,0xBC,0x0E,0xAB,0x86,0x28,0x53,
				0x34,0x9E,0xC7,0x55,0x46,0xF5,0x8F,0xB7,0xC2,0x77,0x5C,0x38,
				0x46,0x2C,0x50,0x10,0xD8,0x46,0xC1,0x85,0xC1,0x51,0x11,0xE5,
				0x95,0x52,0x2A,0x6B,0xCD,0x16,0xCF,0x86,0xF3,0xD1,0x22,0x10,
				0x9E,0x3B,0x1F,0xDD,0x94,0x3B,0x6A,0xEC,0x46,0x8A,0x2D,0x62,
				0x1A,0x7C,0x06,0xC6,0xA9,0x57,0xC6,0x2B,0x54,0xDA,0xFC,0x3B,
				0xE8,0x75,0x67,0xD6,0x77,0x23,0x13,0x95,0xF6,0x14,0x72,0x93,
				0xB6,0x8C,0xEA,0xB7,0xA9,0xE0,0xC5,0x8D,0x86,0x4E,0x8E,0xFD,
				0xE4,0xE1,0xB9,0xA4,0x6C,0xBE,0x85,0x47,0x13,0x67,0x2F,0x5C,
				0xAA,0xAE,0x31,0x4E,0xD9,0x08,0x3D,0xAB,0x4B,0x09,0x9F,0x8E,
				0x30,0x0F,0x01,0xB8,0x65,0x0F,0x1F,0x4B,0x1D,0x8F,0xCF,0x3F,
				0x3C,0xB5,0x3F,0xB8,0xE9,0xEB,0x2E,0xA2,0x03,0xBD,0xC9,0x70,
				0xF5,0x0A,0xE5,0x54,0x28,0xA9,0x1F,0x7F,0x53,0xAC,0x26,0x6B,
				0x28,0x41,0x9C,0x37,0x78,0xA1,0x5F,0xD2,0x48,0xD3,0x39,0xED,
				0xE7,0x85,0xFB,0x7F,0x5A,0x1A,0xAA,0x96,0xD3,0x13,0xEA,0xCC,
				0x89,0x09,0x36,0xC1,0x73,0xCD,0xCD,0x0F,0xAB,0x88,0x2C,0x45,
				0x75,0x5F,0xEB,0x3A,0xED,0x96,0xD4,0x77,0xFF,0x96,0x39,0x0B,
				0xF9,0xA6,0x6D,0x13,0x68,0xB2,0x08,0xE2,0x1F,0x7C,0x10,0xD0,
				0x4A,0x3D,0xBD,0x4E,0x36,0x06,0x33,0xE5,0xDB,0x4B,0x60,0x26,
				0x01,0xC1,0x4C,0xEA,0x73,0x7D,0xB3,0xDC,0xF7,0x22,0x63,0x2C,
				0xC7,0x78,0x51,0xCB,0xDD,0xE2,0xAA,0xF0,0xA3,0x3A,0x07,0xB3,
				0x73,0x44,0x5D,0xF4,0x90,0xCC,0x8F,0xC1,0xE4,0x16,0x0F,0xF1,
				0x18,0x37,0x8F,0x11,0xF0,0x47,0x7D,0xE0,0x55,0xA8,0x1A,0x9E,
				0xDA,0x57,0xA4,0xA2,0xCF,0xB0,0xC8,0x39,0x29,0xD3,0x10,0x91,
				0x2F,0x72,0x9E,0xC6,0xCF,0xA3,0x6C,0x6A,0xC6,0xA7,0x58,0x37,
				0x14,0x30,0x45,0xD7,0x91,0xCC,0x85,0xEF,0xF5,0xB2,0x19,0x32,
				0xF2,0x38,0x61,0xBC,0xF2,0x3A,0x52,0xB5,0xDA,0x67,0xEA,0xF7,
				0xBA,0xAE,0x0F,0x5F,0xB1,0x36,0x9D,0xB7,0x8F,0x3A,0xC4,0x5F,
				0x8C,0x4A,0xC5,0x67,0x1D,0x85,0x73,0x5C,0xDD,0xDB,0x09,0xD2,
				0xB1,0xE3,0x4A,0x1F,0xC0,0x66,0xFF,0x4A,0x16,0x2C,0xB2,0x63,
				0xD6,0x54,0x12,0x74,0xAE,0x2F,0xCC,0x86,0x5F,0x61,0x8A,0xBE,
				0x27,0xC1,0x24,0xCD,0x8B,0x07,0x4C,0xCD,0x51,0x63,0x01,0xB9,
				0x18,0x75,0x82,0x4D,0x09,0x95,0x8F,0x34,0x1E,0xF2,0x74,0xBD,
				0xAB,0x0B,0xAE,0x31,0x63,0x39,0x89,0x43,0x04,0xE3,0x58,0x77,
				0xB0,0xC2,0x8A,0x9B,0x1F,0xD1,0x66,0xC7,0x96,0xB9,0xCC,0x25,
				0x8A,0x06,0x4A,0x8F,0x57,0xE2,0x7F,0x2A,
			};

			auto res = instance.getHash(data, 512, 0);
			for (word32 i = 0; i < out.size(); i++)
			{
				if (out[i] != res[i])
				{
					std::cout << "Shake256 Test failed at index " << i << std::endl;
					std::cin.get();
				}
			}
			std::cout << "Shake256 Test Passed" << std::endl;

			std::cout << "Shake256 working properly! - Hit Enter to continue" << std::endl;

			std::cin.get();
		}
	}
}

#endif

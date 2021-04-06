#ifndef LOCKDOWNSSL_SHA2_TEST
#define LOCKDOWNSSL_SHA2_TEST

#include <iostream>
#include "Sha2.h"


namespace LockdownSSL
{
	namespace Test
	{
		void sha2_224_test()
		{
			auto sha224_instance = LockdownSSL::Hash::Sha2::getInstance_224();

			std::vector<byte> sha224_data_1 = { 'a', 'b', 'c' };

			std::vector<byte> sha224_out_1 =
			{
				0x23,0x09,0x7D,0x22,0x34,0x05,0xD8,
				0x22,0x86,0x42,0xA4,0x77,0xBD,0xA2,
				0x55,0xB3,0x2A,0xAD,0xBC,0xE4,0xBD,
				0xA0,0xB3,0xF7,0xE3,0x6C,0x9D,0xA7,
			};

			// std::vector<byte> sha224_data_2 =
			// {
			// 	'a','b','c','d','b','c','d','e','c',
			// 	'd','e','f','d','e','f','g','e','f',
			// 	'g','h','f','g','h','i','g','h','i',
			// 	'j','h','i','j','k','i','j','k','l',
			// 	'j','k','l','m','k','l','m','n','l',
			// 	'm','n','o','m','n','o','p','n','o',
			// 	'p','q',
			// };
			
			// std::vector<byte> sha224_out_2 =
			// {
			// 	0x75,0x38,0x8B,0x16,0x51,0x27,0x76,
			// 	0xCC,0x5D,0xBA,0x5D,0xA1,0xFD,0x89,
			// 	0x01,0x50,0xB0,0xC6,0x45,0x5C,0xB4,0xF5,
			// 	0x8B,0x19,0x52,0x52,0x25,0x25,
			// };

			auto sha224_res_1 = sha224_instance.getHash(sha224_data_1);
			
			// for (word32 i = 0; i < sha224_out_1.data.size(); i++)
			// {
			// 	if (sha224_out_1.data[i] != sha224_res_1.data[i])
			// 	{
			// 		std::cout << "Sha224 Test 1 failed at index: " << i << std::endl;
			// 		std::cin.get();
			// 		return;
			// 	}
			// }
			// std::cout << "Sha224 Test 1 Passed!" << std::endl;
			std::cout << "Destroy data1" << std::endl;
			sha224_data_1.~vector();

			std::cout << "Destroy Out1" << std::endl;
			sha224_out_1.~vector();

			std::cout << "Destroy res1" << std::endl;
			sha224_res_1.~vector();

			// std::vector<byte> sha224_res_2 = sha224_instance.getHash(sha224_data_2);
			// for (word32 i = 0; i < sha224_out_2.size(); i++)
			// {
			// 	if (sha224_out_2[i] != sha224_res_2[i])
			// 	{
			// 		std::cout << "Sha224 Test 2 failed at index: " << i << std::endl;
			// 		std::cin.get();
			// 		return;
			// 	}
			// }
			// std::cout << "Sha224 Test 2 Passed!" << std::endl;

			// std::cout << "Sha224 working properly! - Hit Enter to continue" << std::endl;

			// std::cin.get();
		}

		void sha2_256_test()
		{
			auto sha256_instance = LockdownSSL::Hash::Sha2::getInstance_256();

			std::vector<byte> sha256_data_1{ 'a', 'b', 'c' };
			std::vector<byte> sha256_out_1
			{
				0xBA,0x78,0x16,0xBF,0x8F,0x01,0xCF,
				0xEA,0x41,0x41,0x40,0xDE,0x5D,0xAE,
				0x22,0x23,0xB0,0x03,0x61,0xA3,0x96,
				0x17,0x7A,0x9C,0xB4,0x10,0xFF,0x61,
				0xF2,0x00,0x15,0xAD,
			};

			std::vector<byte> sha256_data_2
			{
				'a','b','c','d','b','c','d','e','c',
				'd','e','f','d','e','f','g','e','f',
				'g','h','f','g','h','i','g','h','i',
				'j','h','i','j','k','i','j','k','l',
				'j','k','l','m','k','l','m','n','l',
				'm','n','o','m','n','o','p','n','o',
				'p','q',
			};
			std::vector<byte> sha256_out_2
			{
				0x24,0x8D,0x6A,0x61,0xD2,0x06,0x38,
				0xB8,0xE5,0xC0,0x26,0x93,0x0C,0x3E,
				0x60,0x39,0xA3,0x3C,0xE4,0x59,0x64,
				0xFF,0x21,0x67,0xF6,0xEC,0xED,0xD4,
				0x19,0xDB,0x06,0xC1,
			};

			std::vector<byte> sha256_res_1 = sha256_instance.getHash(sha256_data_1);
			for (word32 i = 0; i < sha256_out_1.size(); i++)
			{
				if (sha256_out_1[i] != sha256_res_1[i])
				{
					std::cout << "Sha256 Test 1 failed at index: " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Sha256 Test 1 Passed!" << std::endl;

			std::vector<byte> sha256_res_2 = sha256_instance.getHash(sha256_data_2);
			for (word32 i = 0; i < sha256_out_2.size(); i++)
			{
				if (sha256_out_2[i] != sha256_res_2[i])
				{
					std::cout << "Sha256 Test 2 failed at index: " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Sha256 Test 2 Passed!" << std::endl;

			std::cout << "Sha256 working properly! - Hit Enter to continue" << std::endl;

			std::cin.get();
		}

		void sha2_384_test()
		{
			auto sha384_instance = LockdownSSL::Hash::Sha2::getInstance_384();

			std::vector<byte> sha384_data_1{ 'a', 'b', 'c' };
			std::vector<byte> sha384_data_2
			{
				'a','b','c','d','e','f','g','h',
				'b','c','d','e','f','g','h','i',
				'c','d','e','f','g','h','i','j',
				'd','e','f','g','h','i','j','k',
				'e','f','g','h','i','j','k','l',
				'f','g','h','i','j','k','l','m',
				'g','h','i','j','k','l','m','n',
				'h','i','j','k','l','m','n','o',
				'i','j','k','l','m','n','o','p',
				'j','k','l','m','n','o','p','q',
				'k','l','m','n','o','p','q','r',
				'l','m','n','o','p','q','r','s',
				'm','n','o','p','q','r','s','t',
				'n','o','p','q','r','s','t','u',
			};

			std::vector<byte> sha384_out_1
			{
				0xCB,0x00,0x75,0x3F,0x45,0xA3,0x5E,
				0x8B,0xB5,0xA0,0x3D,0x69,0x9A,0xC6,
				0x50,0x07,0x27,0x2C,0x32,0xAB,0x0E,
				0xDE,0xD1,0x63,0x1A,0x8B,0x60,0x5A,
				0x43,0xFF,0x5B,0xED,0x80,0x86,0x07,
				0x2B,0xA1,0xE7,0xCC,0x23,0x58,0xBA,
				0xEC,0xA1,0x34,0xC8,0x25,0xA7,
			};

			std::vector<byte> sha384_out_2
			{
				0x09,0x33,0x0C,0x33,0xF7,0x11,0x47,
				0xE8,0x3D,0x19,0x2F,0xC7,0x82,0xCD,
				0x1B,0x47,0x53,0x11,0x1B,0x17,0x3B,
				0x3B,0x05,0xD2,0x2F,0xA0,0x80,0x86,
				0xE3,0xB0,0xF7,0x12,0xFC,0xC7,0xC7,
				0x1A,0x55,0x7E,0x2D,0xB9,0x66,0xC3,
				0xE9,0xFA,0x91,0x74,0x60,0x39,
			};

			std::vector<byte> sha384_res_1 = sha384_instance.getHash(sha384_data_1);
			for (word32 i = 0; i < sha384_out_1.size(); i++)
			{
				if (sha384_out_1[i] != sha384_res_1[i])
				{
					std::cout << "Sha384 Test 1 failed at index: " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Sha384 Test 1 Passed!" << std::endl;

			std::vector<byte> sha384_res_2 = sha384_instance.getHash(sha384_data_2);
			for (word32 i = 0; i < sha384_out_2.size(); i++)
			{
				if (sha384_out_2[i] != sha384_res_2[i])
				{
					std::cout << "Sha384 Test 2 failed at index: " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Sha384 Test 2 Passed!" << std::endl;

			std::cout << "Sha384 working properly! - Hit Enter to continue" << std::endl;

			std::cin.get();
		}

		void sha2_512_test()
		{
			auto sha512_instance = LockdownSSL::Hash::Sha2::getInstance_512();

			std::vector<byte> sha512_data_1{ 'a', 'b', 'c' };
			std::vector<byte> sha512_data_2
			{
				'a','b','c','d','e','f','g','h',
				'b','c','d','e','f','g','h','i',
				'c','d','e','f','g','h','i','j',
				'd','e','f','g','h','i','j','k',
				'e','f','g','h','i','j','k','l',
				'f','g','h','i','j','k','l','m',
				'g','h','i','j','k','l','m','n',
				'h','i','j','k','l','m','n','o',
				'i','j','k','l','m','n','o','p',
				'j','k','l','m','n','o','p','q',
				'k','l','m','n','o','p','q','r',
				'l','m','n','o','p','q','r','s',
				'm','n','o','p','q','r','s','t',
				'n','o','p','q','r','s','t','u',
			};

			std::vector<byte> sha512_out_1
			{
				0xDD,0xAF,0x35,0xA1,0x93,0x61,0x7A,0xBA,
				0xCC,0x41,0x73,0x49,0xAE,0x20,0x41,0x31,
				0x12,0xE6,0xFA,0x4E,0x89,0xA9,0x7E,0xA2,
				0x0A,0x9E,0xEE,0xE6,0x4B,0x55,0xD3,0x9A,
				0x21,0x92,0x99,0x2A,0x27,0x4F,0xC1,0xA8,
				0x36,0xBA,0x3C,0x23,0xA3,0xFE,0xEB,0xBD,
				0x45,0x4D,0x44,0x23,0x64,0x3C,0xE8,0x0E,
				0x2A,0x9A,0xC9,0x4F,0xA5,0x4C,0xA4,0x9F,
			};

			std::vector<byte> sha512_out_2
			{
				0x8E,0x95,0x9B,0x75,0xDA,0xE3,0x13,0xDA,
				0x8C,0xF4,0xF7,0x28,0x14,0xFC,0x14,0x3F,
				0x8F,0x77,0x79,0xC6,0xEB,0x9F,0x7F,0xA1,
				0x72,0x99,0xAE,0xAD,0xB6,0x88,0x90,0x18,
				0x50,0x1D,0x28,0x9E,0x49,0x00,0xF7,0xE4,
				0x33,0x1B,0x99,0xDE,0xC4,0xB5,0x43,0x3A,
				0xC7,0xD3,0x29,0xEE,0xB6,0xDD,0x26,0x54,
				0x5E,0x96,0xE5,0x5B,0x87,0x4B,0xE9,0x09,
			};

			std::vector<byte> sha512_res_1 = sha512_instance.getHash(sha512_data_1);
			for (word32 i = 0; i < sha512_out_1.size(); i++)
			{
				if (sha512_out_1[i] != sha512_res_1[i])
				{
					std::cout << "Sha512 Test 1 failed at index: " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Sha512 Test 1 Passed!" << std::endl;

			std::vector<byte> sha512_res_2 = sha512_instance.getHash(sha512_data_2);
			for (word32 i = 0; i < sha512_out_2.size(); i++)
			{
				if (sha512_out_2[i] != sha512_res_2[i])
				{
					std::cout << "Sha512 Test 2 failed at index: " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Sha512 Test 2 Passed!" << std::endl;

			std::cout << "Sha512 working properly! - Hit Enter to continue" << std::endl;

			std::cin.get();
		}

		void sha2_512_224_test()
		{
			auto sha512_224_instance = LockdownSSL::Hash::Sha2::getInstance_512_224();

			std::vector<byte> sha512_224_data_1{ 'a', 'b', 'c' };
			std::vector<byte> sha512_224_data_2
			{
				'a','b','c','d','e','f','g','h',
				'b','c','d','e','f','g','h','i',
				'c','d','e','f','g','h','i','j',
				'd','e','f','g','h','i','j','k',
				'e','f','g','h','i','j','k','l',
				'f','g','h','i','j','k','l','m',
				'g','h','i','j','k','l','m','n',
				'h','i','j','k','l','m','n','o',
				'i','j','k','l','m','n','o','p',
				'j','k','l','m','n','o','p','q',
				'k','l','m','n','o','p','q','r',
				'l','m','n','o','p','q','r','s',
				'm','n','o','p','q','r','s','t',
				'n','o','p','q','r','s','t','u',
			};

			std::vector<byte> sha512_224_out_1
			{
				0x46,0x34,0x27,0x0F,0x70,0x7B,0x6A,
				0x54,0xDA,0xAE,0x75,0x30,0x46,0x08,
				0x42,0xE2,0x0E,0x37,0xED,0x26,0x5C,
				0xEE,0xE9,0xA4,0x3E,0x89,0x24,0xAA,
			};

			std::vector<byte> sha512_224_out_2
			{
				0x23,0xFE,0xC5,0xBB,0x94,0xD6,0x0B,
				0x23,0x30,0x81,0x92,0x64,0x0B,0x0C,
				0x45,0x33,0x35,0xD6,0x64,0x73,0x4F,
				0xE4,0x0E,0x72,0x68,0x67,0x4A,0xF9,
			};

			std::vector<byte> sha512_224_res_1 = sha512_224_instance.getHash(sha512_224_data_1);
			for (word32 i = 0; i < sha512_224_out_1.size(); i++)
			{
				if (sha512_224_out_1[i] != sha512_224_res_1[i])
				{
					std::cout << "Sha512_224 Test 1 failed at index: " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Sha512_224 Test 1 Passed!" << std::endl;

			std::vector<byte> sha512_224_res_2 = sha512_224_instance.getHash(sha512_224_data_2);
			for (word32 i = 0; i < sha512_224_out_2.size(); i++)
			{
				if (sha512_224_out_2[i] != sha512_224_res_2[i])
				{
					std::cout << "Sha512_224 Test 2 failed at index: " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Sha512_224 Test 2 Passed!" << std::endl;

			std::cout << "Sha512_224 working properly! - Hit Enter to continue" << std::endl;

			std::cin.get();
		}

		void sha2_512_256_test()
		{
			auto sha512_256_instance = LockdownSSL::Hash::Sha2::getInstance_512_256();

			std::vector<byte> sha512_256_data_1{ 'a', 'b', 'c' };
			std::vector<byte> sha512_256_data_2
			{
				'a','b','c','d','e','f','g','h',
				'b','c','d','e','f','g','h','i',
				'c','d','e','f','g','h','i','j',
				'd','e','f','g','h','i','j','k',
				'e','f','g','h','i','j','k','l',
				'f','g','h','i','j','k','l','m',
				'g','h','i','j','k','l','m','n',
				'h','i','j','k','l','m','n','o',
				'i','j','k','l','m','n','o','p',
				'j','k','l','m','n','o','p','q',
				'k','l','m','n','o','p','q','r',
				'l','m','n','o','p','q','r','s',
				'm','n','o','p','q','r','s','t',
				'n','o','p','q','r','s','t','u',
			};

			std::vector<byte> sha512_256_out_1
			{
				0x53,0x04,0x8E,0x26,0x81,0x94,0x1E,
				0xF9,0x9B,0x2E,0x29,0xB7,0x6B,0x4C,
				0x7D,0xAB,0xE4,0xC2,0xD0,0xC6,0x34,
				0xFC,0x6D,0x46,0xE0,0xE2,0xF1,0x31,
				0x07,0xE7,0xAF,0x23,
			};

			std::vector<byte> sha512_256_out_2
			{
				0x39,0x28,0xE1,0x84,0xFB,0x86,0x90,
				0xF8,0x40,0xDA,0x39,0x88,0x12,0x1D,
				0x31,0xBE,0x65,0xCB,0x9D,0x3E,0xF8,
				0x3E,0xE6,0x14,0x6F,0xEA,0xC8,0x61,
				0xE1,0x9B,0x56,0x3A,
			};

			std::vector<byte> sha512_256_res_1 = sha512_256_instance.getHash(sha512_256_data_1);
			for (word32 i = 0; i < sha512_256_out_1.size(); i++)
			{
				if (sha512_256_out_1[i] != sha512_256_res_1[i])
				{
					std::cout << "Sha512_256 Test 1 failed at index: " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Sha512_256 Test 1 Passed!" << std::endl;

			std::vector<byte> sha512_256_res_2 = sha512_256_instance.getHash(sha512_256_data_2);
			for (word32 i = 0; i < sha512_256_out_2.size(); i++)
			{
				if (sha512_256_out_2[i] != sha512_256_res_2[i])
				{
					std::cout << "Sha512_256 Test 2 failed at index: " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Sha512_256 Test 2 Passed!" << std::endl;

			std::cout << "Sha512_256 working properly! - Hit Enter to continue" << std::endl;

			std::cin.get();
		}
	}
}

#endif
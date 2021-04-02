#include "misc/Endianness.h"

template<> byte bReverseEndianness<byte>(byte Value)
{
    return ( Value * 0x0202020202ULL & 0x010884422010ULL ) % 1023;
}
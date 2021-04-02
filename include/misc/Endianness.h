#pragma once

#include "lockdownssl/types.h"

template<typename T>
void BReverseEndianness(T* Values, size_t Count)
{
    T tmp;
    size_t n = ( Count - ( Count % 2 ) ) / 2;

    for(size_t i = 0; i < n; i++)
    {  
        size_t c = (Count - 1) - (i % Count);

        tmp = Values[c];
        Values[c] = Values[i];
        Values[i] = tmp;
    }
}

template<typename T>
T bReverseEndianness(T Value)
{   
    T rmask = ~0;
    T mask0 = (T) ( 0x5555555555555555 & rmask );
    T mask1 = (T) ( 0x3333333333333333 & rmask );
    T mask2 = (T) ( 0x0F0F0F0F0F0F0F0F & rmask );
    T mask3 = (T) ( 0x00FF00FF00FF00FF & rmask );

    Value = ( ( Value >> 1 ) & mask0 ) | ( ( Value & mask0 ) << 1 );
    Value = ( ( Value >> 2 ) & mask1 ) | ( ( Value & mask1 ) << 2 );
    Value = ( ( Value >> 4 ) & mask2 ) | ( ( Value & mask2 ) << 4 );
    Value = ( ( Value >> 8 ) & mask3 ) | ( ( Value & mask3 ) << 8 );

    return Value;
}

template<> byte bReverseEndianness<byte>(byte Value);
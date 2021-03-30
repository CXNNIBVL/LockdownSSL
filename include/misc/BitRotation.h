#pragma once

template<typename T>
inline T rotl(T val, unsigned int count)
{
    return ( val << count ) | ( val >> ( ( sizeof(T) * 8 ) - count ) );
}

template<typename T>
inline T rotr(T val, unsigned int count)
{
    return ( val >> count ) | ( val << ( (sizeof(T) * 8 ) - count ) );
}
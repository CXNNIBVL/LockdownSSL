#include <utility>

#include "pipeline/Hex.h"

const char uHexChars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
const char lHexChars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

byte hex_to_byte(byte b)
{
    if(b >= '0' && b <= '9')
        return b - '0';
    else if(b >= 'A' && b <= 'F')
        return b - 'A' + 10;
    else if(b >= 'a' && b <= 'f')
        return b - 'a' + 10;
    else return 16;
}

namespace LockdownSSL::Pipeline
{
    void HexEncoder::ProcessData(SecureBlock<byte>& Data)
    {
        const char* hex_chars = m_Config.m_Case == m_Config.UPPERCASE ? uHexChars : lHexChars;
        size_t len_header = m_Config.m_Header.size();
        size_t len_seperator = m_Config.m_Seperator.size();
        size_t len_terminator = m_Config.m_Terminator.size();

        SecureBlock<byte> hexString;

        hexString.Grow(len_header);
        for(size_t a = 0; a < len_header; a++)
            hexString[a] = m_Config.m_Header[a];
        
        size_t i = len_header;
        size_t group_ctr = 0;
        for(SecureBlock<byte>::Iterator it = Data.begin(); it != Data.end(); it++)
        {
            group_ctr++;

            hexString.Grow(2);
            hexString[i++] = hex_chars[ ( *it & 0xF0 ) >> 4 ];
            hexString[i++] = hex_chars[ ( *it & 0x0F ) ];

            if(group_ctr == m_Config.m_GroupSize && ( it + m_Config.m_GroupSize ) !=  &(Data.end()[0]))
            {
                group_ctr = 0;

                hexString.Grow(len_seperator);

                for(size_t a = 0; a < len_seperator; a++, i++)
                    hexString[i] = m_Config.m_Seperator[a];
            }
        }

        hexString.Grow(len_terminator);
        for(size_t a = 0; a < len_terminator; a++, i++)
            hexString[i] = m_Config.m_Terminator[a];

        Data = std::move(hexString);

        if(m_AttatchedTransformation)
            m_AttatchedTransformation->ProcessData(Data);
    }

    void HexDecoder::ProcessData(SecureBlock<byte>& Data)
    {
        SecureBlock<byte> decoded;
        byte buf1, buf2;

        for(size_t i = 0; i < Data.Size(); i++)
        {
            buf1 = hex_to_byte(Data[i]);
            buf2 = hex_to_byte(Data[i + 1]);

            if(buf1 < 16 && buf2 < 16)
            {
                decoded.Grow(1);
                decoded[decoded.Size() - 1] = ( buf1 << 4) | buf2;
                i++;
            }
        }

        Data = std::move(decoded);

        if(m_AttatchedTransformation)
            m_AttatchedTransformation->ProcessData(Data);
    }
}
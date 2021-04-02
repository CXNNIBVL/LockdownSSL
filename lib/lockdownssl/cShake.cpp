#include "lockdownssl/Shake.h"

using namespace LockdownSSL;

static void LeftEncode()
{
    
}

static void RightEncode()
{

}

void cShake_128::Digest(SecureBlock<byte>& Data)
{
    if(!m_EncodeString)
    {
        m_Keccak.Digest(Data);
        return;
    }
}

void cShake_256::Digest(SecureBlock<byte>& Data)
{
    if(!m_EncodeString)
    {
        m_Keccak.Digest(Data);
        return;
    }
}
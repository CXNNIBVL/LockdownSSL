#include "pipeline/HashTransformation.h"

using namespace LockdownSSL::Pipeline;

void HashTransformation::ProcessData(SecureBlock<byte>& Data) { m_HashFunction.Digest(Data); }
#include "vector/setup.h"

/* ===== SHA3 / KECCAK ===== */
#include "vector/vKeccak.h" 

int main()
{
    VerifyKeccak();
    
    PrintFailed();
    
    std::cout << "***** TESTS FINISHED *****" << std::endl;
    return 0;
}
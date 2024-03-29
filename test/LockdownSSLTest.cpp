#include "vector/setup.h"

/* ===== SHA3 / KECCAK ===== */
#include "vector/vKeccak.h"

/* ===== KANGAROOTWELVE / MARSUPILAMI ===== */
#include "vector/vKangarooTwelve.h" 

std::string logo = "\r\n    __               __       __                   __________ __ \r\n   \/ \/   ____  _____\/ \/______\/ \/___ _      ______ \/ ___\/ ___\/\/ \/ \r\n  \/ \/   \/ __ \\\/ ___\/ \/\/_\/ __  \/ __ \\ | \/| \/ \/ __ \\\\__ \\\\__ \\\/ \/  \r\n \/ \/___\/ \/_\/ \/ \/__\/ ,< \/ \/_\/ \/ \/_\/ \/ |\/ |\/ \/ \/ \/ \/__\/ \/__\/ \/ \/___\r\n\/_____\/\\____\/\\___\/_\/|_|\\__,_\/\\____\/|__\/|__\/_\/ \/_\/____\/____\/_____\/\r\n ";
std::string sep = "********************************************************************************\n";

int main()
{
    std::cout << sep << logo << "\n\n" << sep << std::endl;

    std::cout << "***** TESTS *****" << std::endl;

    VerifyKeccak();
    VerifyKangarooTwelve();
    
    PrintFailed();

    std::cout << "***** TESTS FINISHED *****" << std::endl;
    
    return 0;
}
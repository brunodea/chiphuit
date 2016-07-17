#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

//#define NDEBUG // disable asserts

#include "macros.h"
#include "chiphuit.h"

int main(int argc, char *argv[])
{
    using std::cout;
    using std::endl;

    if (argc == 2)
    {
        cout << "****************************\n";
        cout << "* Chip Huit by Bruno de A. *\n";
        cout << "****************************\n";

        std::ifstream rom_stream(argv[1], std::ios::binary);
        std::vector<byte> rom(
                (std::istreambuf_iterator<char>(rom_stream)),
                (std::istreambuf_iterator<char>()));
        chu::ChipHuit chip_huit(rom);
        chip_huit.start();
    }
    else
        std::cerr << "Usage: ./chiphuit path/to/rom\n";

    return 0;
}

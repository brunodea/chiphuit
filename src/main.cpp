#include <iostream>

#include "cpu.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "****************************" << endl;
    cout << "* Chip Huit by Bruno de A. *" << endl;
    cout << "****************************" << endl;

    chu::Cpu cpu;
    cpu.run();
    return 0;
}

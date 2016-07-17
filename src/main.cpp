#include <iostream>

#include "cpu.h"


int main()
{
    using std::cout;
    using std::endl;

    cout << "****************************" << endl;
    cout << "* Chip Huit by Bruno de A. *" << endl;
    cout << "****************************" << endl;

    chu::cpu::Cpu cpu;
    cpu.run();
    return 0;
}

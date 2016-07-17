#include "chiphuit.h"
#include <iostream>

#include "mem.h"

using namespace chu;

ChipHuit::ChipHuit()
    : m_Instrs()
{
    m_Cpu = std::make_unique<cpu::Cpu>();
    m_Memory = std::make_unique<mem::Memory>();
    // initialize instructions array.
    for (word i = 0; i < NUMBER_OF_INSTRS; ++i)
    {
        m_Instrs[i] = cpu::Instruction(i, m_Cpu.get(), m_Memory.get());
        auto s = m_Instrs[i].to_string();
        if (!s.empty())
            std::cout << s << '\n';
    }
}

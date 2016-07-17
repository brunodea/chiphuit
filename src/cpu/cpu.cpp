#include "cpu.h"

#include <iostream>
#include <cstring>

using namespace chu::cpu;

Cpu::Cpu()
    : m_MemReg(0), m_DelayReg(0), m_SoundReg(0), m_Instrs()
{
    // Initialize registers with 0.
    std::memset(m_GenRegs, 0, sizeof m_GenRegs);

    // initialize instructions array.
    for (word i = 0; i < NUMBER_OF_INSTRS; ++i)
    {
        m_Instrs[i] = Instruction(i);
    }
}

void Cpu::run()
{
}

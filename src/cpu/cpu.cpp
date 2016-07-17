#include "cpu.h"

#include <iostream>
#include <cstring> // memset

using namespace chu::cpu;

Cpu::Cpu()
    : m_MemReg(0), m_DelayReg(0), m_SoundReg(0)
{
    // Initialize registers with 0.
    std::memset(m_GenRegs, 0, sizeof m_GenRegs);

}

void Cpu::run()
{
}

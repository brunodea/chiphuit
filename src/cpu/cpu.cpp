#include "cpu.h"

#include <iostream>
#include <cstring> // memset

using namespace chu::cpu;

Cpu::Cpu(mem::Memory *memory)
    : m_MemReg(0), m_DelayReg(0), m_SoundReg(0), m_Memory(memory)
{
    // Initialize registers with 0.
    std::memset(m_GenRegs, 0, sizeof m_GenRegs);
    m_PC = MEMORY_ROM_START_ADDR;

    // initialize instructions array.
    for (word i = 0; i < NUMBER_OF_INSTRS; ++i)
    {
        m_OpcodeInstrMap[i] = std::make_unique<Instruction>(i, this, m_Memory);
    }
}

void Cpu::run()
{
    while (true)
    {
        auto msb = m_Memory->read(m_PC++);
        auto lsb = m_Memory->read(m_PC);

        auto opcode = (static_cast<word>(msb) << 8) | lsb;
        auto instr = m_OpcodeInstrMap[opcode].get();
        std::cout << instr->to_string() << '\n';
        instr->execute();
    }
}

}

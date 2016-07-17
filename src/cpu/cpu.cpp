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

byte Cpu::pop_stack_byte()
{
    return m_Memory->read(m_SP--);
}

word Cpu::pop_stack_word()
{
    auto lsb = pop_stack_byte();
    auto msb = pop_stack_byte();

    return (static_cast<word>(msb) << 8) | lsb;
}

void Cpu::push_stack_byte(const byte &b)
{
    m_SP++;
    m_Memory->write(m_SP, b);
}

void Cpu::push_stack_word(const word &w)
{
    auto lsb = w & 0x00FF;
    auto msb = w & 0xFF00;
    push_stack_byte(msb);
    push_stack_byte(lsb);
}

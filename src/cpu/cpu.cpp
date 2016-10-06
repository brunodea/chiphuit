#include "cpu.h"

#include <iostream>
#include <iomanip> // std::setfill // std::setw
#include <cstring> // memset

#include "instr.h"

using namespace chu::cpu;

Cpu::Cpu(mem::Memory *memory, video::Video *video)
    : m_MemReg(0), m_DelayReg(0), m_SoundReg(0),
    m_PC(MEMORY_ROM_START_ADDR), m_SP(0), m_Memory(memory), m_Video(video), m_StackArray{ 0 }
{
    // Initialize registers with 0.
    std::memset(m_GenRegs, 0, sizeof m_GenRegs);

    // initialize instructions array.
    m_OpcodeMap = std::make_unique<OpcodeMap>();
    for (word i = 0; i < NUMBER_OF_INSTRS; ++i)
    {
        (*m_OpcodeMap)[i] = Instruction { i, this, m_Memory, m_Video };
    }
}

Instruction Cpu::step()
{
    auto instr = next();
    instr.execute();
    return instr;
}

Instruction Cpu::next()
{
    return (*m_OpcodeMap)[m_Memory->read_word(m_PC)];
}

byte Cpu::pop_stack_byte()
{
    return m_StackArray[m_SP--];
}

word Cpu::pop_stack_word()
{
    auto lsb = pop_stack_byte();
    auto msb = pop_stack_byte();

    return (static_cast<word>(msb) << 8) | lsb;
}

void Cpu::push_stack_byte(const byte b)
{
    m_StackArray[++m_SP] = b;
}

void Cpu::push_stack_word(const word w)
{
    auto lsb = w & 0x00FF;
    auto msb = (w & 0xFF00) >> 8;
    push_stack_byte(msb);
    push_stack_byte(lsb);
}

void Cpu::update_delay_register()
{
    m_DelayReg = m_DelayReg == 0 ? 0 : m_DelayReg - 1;
}

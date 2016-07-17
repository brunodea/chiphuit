#include "chiphuit.h"
#include <iostream>

#include "mem.h"

using namespace chu;

ChipHuit::ChipHuit(const std::vector<byte> &rom)
    : m_Instrs()
{
    m_Cpu = std::make_unique<cpu::Cpu>();
    m_Memory = std::make_unique<mem::Memory>();
    m_Memory->load_rom(rom);
    // initialize instructions array.
    for (word i = 0; i < NUMBER_OF_INSTRS; ++i)
    {
        m_Instrs[i] = cpu::Instruction(i, m_Cpu.get(), m_Memory.get());
    }
}

void ChipHuit::start()
{
    word start_addr = MEMORY_ROM_START_ADDR;
    for (auto i = start_addr; i < MEMORY_SIZE_IN_BYTES; ++i)
    {
        auto msb = m_Memory->read(i++);
        auto lsb = m_Memory->read(i);

        auto opcode = (static_cast<word>(msb) << 8) | lsb;
        if (opcode != 0)
            std::cout << m_Instrs[opcode].to_string() << '\n';
    }
}

#include "chiphuit.h"
#include <iostream>

#include "mem.h"

using namespace chu;

ChipHuit::ChipHuit(const std::vector<byte> &rom)
{
    m_Memory = std::make_unique<mem::Memory>();
    m_Memory->load_rom(rom);
    m_Cpu = std::make_unique<cpu::Cpu>(m_Memory.get());
}

void ChipHuit::start()
{
    m_Cpu->run();
}

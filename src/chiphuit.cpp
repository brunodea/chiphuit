#include "chiphuit.h"

#include "mem.h"

using namespace chu;

ChipHuit::ChipHuit(const std::vector<byte> &rom)
{
    m_Memory = std::make_unique<mem::Memory>();
    m_Memory->load_rom(rom);

#ifndef NDEBUG
    m_Memory->print_chunk(MEMORY_ROM_START_ADDR, MEMORY_ROM_START_ADDR+rom.size());
#endif

    m_Cpu = std::make_unique<cpu::Cpu>(m_Memory.get());
}

void ChipHuit::start()
{
    m_Cpu->run();
}

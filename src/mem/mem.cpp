#include "mem.h"

#include <cstring> // memset
#include <assert.h>

using namespace chu::mem;

Memory::Memory()
{
    // init memory with 0s
    std::memset(m_Memory, 0, sizeof m_Memory);
}

byte Memory::read(const word &address) const
{
    assert(address < MEMORY_SIZE_IN_BYTES);
    return m_Memory[address];
}

void Memory::write(const word &address, const byte &value)
{
    assert(address < MEMORY_SIZE_IN_BYTES);
    m_Memory[address] = value;
}

void Memory::load_rom(const std::vector<byte> &rom)
{
    word address = MEMORY_ROM_START_ADDR;
    for (const auto &b : rom)
    {
        m_Memory[address] = b;
        address++;
    }
}

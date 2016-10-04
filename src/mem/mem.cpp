#include "mem.h"

#include <iostream>
#include <iomanip>
#include <cstring> // memset
#include <assert.h>
#include <algorithm>

using namespace chu::mem;

Memory::Memory()
{
    // init memory with 0s
    std::memset(m_Memory, 0, sizeof m_Memory);
}

byte Memory::read(const word address) const
{
    assert(address < MEMORY_SIZE_IN_BYTES);
    return m_Memory[address];
}

word Memory::read_word(const word address) const
{
    auto msb = read(address);
    auto lsb = read(address+1);
    return (static_cast<word>(msb) << 8) | lsb;
}

void Memory::write(const word address, const byte value)
{
    assert(address < MEMORY_SIZE_IN_BYTES);
    m_Memory[address] = value;
}

void Memory::load_rom(const std::vector<byte> &rom)
{
//    assert(rom.size() < MEMORY_SIZE_IN_BYTES - MEMORY_ROM_START_ADDR);
//    for (int i = 0; i < rom.size() - 1; i += 2)
//    {
//        m_Memory[i + MEMORY_ROM_START_ADDR] = rom[i + 1];
//        m_Memory[i + MEMORY_ROM_START_ADDR + 1] = rom[i];
//    }
    std::copy_n(rom.begin(), rom.size(), &m_Memory[MEMORY_ROM_START_ADDR]);
}

std::vector<byte> Memory::chunk(const word start_address, word end_address) const
{
    if (start_address >= end_address)
        return std::vector<byte>();
    if (end_address >= MEMORY_SIZE_IN_BYTES)
        end_address = MEMORY_SIZE_IN_BYTES;

    return std::vector<byte>(&m_Memory[start_address], &m_Memory[end_address]);
}

void Memory::print_chunk(const word start_address, const word end_address) const
{
    auto ch = chunk(start_address, end_address);
    auto j = 0;
    auto t = 0;
    auto addr = start_address;
    std::cout << std::setfill('0') << std::setw(6) << std::hex << int(addr) << ": ";
    for (auto i = 0; i < ch.size(); ++i)
    {
        std::cout << std::setfill('0') << std::setw(2) << std::hex << int(ch[i]) << ' ';

        j++;
        t++;
        if (j == 16)
        {
            addr += j;
            j = 0;
            std::cout << std::endl;
            std::cout << std::setfill('0') << std::setw(6) << std::hex << int(addr) << ": ";
            t = 0;
        }
        if (t == 2)
        {
            t = 0;
            std::cout << ' ';
        }
    }
    std::cout << std::endl;
}

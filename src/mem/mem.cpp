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

byte Memory::read(const word &address) const
{
    assert(address < MEMORY_SIZE_IN_BYTES);
    return m_Memory[address];
}

word Memory::read_word(const word &address) const
{
    auto msb = read(address);
    auto lsb = read(address+1);
    return (static_cast<word>(msb) << 8) | lsb;
}

void Memory::write(const word &address, const byte &value)
{
    assert(address < MEMORY_SIZE_IN_BYTES);
    m_Memory[address] = value;
}

void Memory::load_rom(const std::vector<byte> &rom)
{
    assert(rom.size() < MEMORY_SIZE_IN_BYTES - MEMORY_ROM_START_ADDR);
    std::copy_n(rom.begin(), rom.size(), &m_Memory[MEMORY_ROM_START_ADDR]);
}

std::vector<byte> Memory::chunk(const word &start_address, const word &end_address)
{
    assert(start_address < end_address);
    assert(end_address < MEMORY_SIZE_IN_BYTES);

    return std::vector<byte>(&m_Memory[start_address], &m_Memory[end_address]);
}

void Memory::print_chunk(const word &start_address, const word &end_address)
{
    auto ch = chunk(start_address, end_address);
    auto j = 0;
    auto t = 0;
    for (auto i = 0; i < ch.size(); ++i)
    {
        std::cout << std::setfill('0') << std::setw(2) << std::hex << int(ch[i]);

        j++;
        t++;
        if (j == 16)
        {
            j = 0;
            std::cout << '\n';
            t = 0;
        }
        if (t == 2)
        {
            t = 0;
            std::cout << ' ';
        }
    }
    std::cout << "\n";
}

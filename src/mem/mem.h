#pragma once

#include <vector>
#include "util/macros.h"

namespace chu
{
namespace mem
{
    class Memory
    {
    public:
        Memory();

        void load_rom(const std::vector<byte> &rom);

        byte read(const word &address) const;
        word read_word(const word &start_address) const;
        void write(const word &address, const byte &value);

        std::vector<byte> chunk(const word &start_address, const word &end_address);
        void print_chunk(const word &start_address, const word &end_address);
    private:
        byte m_Memory[MEMORY_SIZE_IN_BYTES];
    };
} // end of namespace mem
} // end of namespace chu

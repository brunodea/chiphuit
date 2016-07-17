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
        void write(const word &address, const byte &value);

    private:
        byte m_Memory[MEMORY_SIZE_IN_BYTES];
    };
} // end of namespace mem
} // end of namespace chu

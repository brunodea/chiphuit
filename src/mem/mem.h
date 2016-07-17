#pragma once

#include "util/macros.h"

namespace chu
{
namespace mem
{
    class Memory
    {
    public:
        Memory();

        byte read(const word &address) const;
        void write(const word &address, const byte &value);

    private:
        byte m_Memory[MEMORY_SIZE_IN_BYTES];
    };
} // end of namespace mem
} // end of namespace chu

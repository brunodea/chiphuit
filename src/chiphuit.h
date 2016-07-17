#pragma once

#include <memory>

#include "cpu.h"
#include "mem.h"
#include "instr.h"
#include "macros.h"

namespace chu
{
    class ChipHuit
    {
    public:
        ChipHuit();
    private:
        cpu::Instruction m_Instrs[NUMBER_OF_INSTRS]; // for instruction translation
        std::unique_ptr<cpu::Cpu> m_Cpu;
        std::unique_ptr<mem::Memory> m_Memory;
    };
} // end of namespace chu

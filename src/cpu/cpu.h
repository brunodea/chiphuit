#pragma once

#include "util/macros.h"
#include "instr.h"

namespace chu
{
namespace cpu
{
    class Instruction;

    class Cpu
    {
    friend class Instruction;
    public:
        Cpu();

        void run();

    private:
        SReg m_GenRegs[NUMBER_OF_GENREGS]; // general purpose registers

        SReg m_FlagReg; // flag register
        DReg m_MemReg; // register I (holds memory addresses)
        SReg m_DelayReg; // delay timer register
        SReg m_SoundReg; // sound timer register

        DReg m_PC; // program counter
        DReg m_SP; // stack pointer
    }; // end of class Cpu

} // end of namespace cpu
} // end of namespace chu

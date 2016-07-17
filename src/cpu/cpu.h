#pragma once

#include <memory>

#include "util/macros.h"
#include "instr.h"
#include "mem.h"

namespace chu
{
namespace cpu
{
    class Instruction;

    class Cpu
    {
    friend class Instruction;
    public:
        Cpu(mem::Memory *memory);

        void run();
    private:
        byte pop_stack_byte();
        word pop_stack_word();

        void push_stack_byte(const byte &b);
        void push_stack_word(const word &w);

    private:
        SReg m_GenRegs[NUMBER_OF_GENREGS]; // general purpose registers

        SReg m_FlagReg; // flag register
        DReg m_MemReg; // register I (holds memory addresses)
        SReg m_DelayReg; // delay timer register
        SReg m_SoundReg; // sound timer register

        DReg m_PC; // program counter
        DReg m_SP; // stack pointer

        mem::Memory *m_Memory;
        std::unique_ptr<Instruction> m_OpcodeInstrMap[NUMBER_OF_INSTRS];
    }; // end of class Cpu

} // end of namespace cpu
} // end of namespace chu

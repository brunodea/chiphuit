#pragma once

#include <memory>
#include <array>

#include "util/macros.h"
#include "instr.h"
#include "mem.h"
#include "video.h"
#include "debugger.h"

namespace chu
{
namespace dbg
{
    class Debugger;
} // end of namespace dbg

namespace cpu
{
    class Instruction;
    using OpcodeMap = std::array<Instruction, NUMBER_OF_INSTRS>;

    class Cpu
    {
    friend class dbg::Debugger;
    friend class Instruction;

    public:
        Cpu(mem::Memory *memory, video::Video *video);

        Instruction step();
        Instruction next();
        void update_delay_register();

    private:
        byte pop_stack_byte();
        word pop_stack_word();

        void push_stack_byte(const byte b);
        void push_stack_word(const word w);

    private:
        SReg m_GenRegs[NUMBER_OF_GENREGS]; // general purpose registers

        SReg m_FlagReg; // flag register
        DReg m_MemReg; // register I (holds memory addresses)
        SReg m_DelayReg; // delay timer register
        SReg m_SoundReg; // sound timer register

        DReg m_PC; // program counter
        DReg m_SP; // stack pointer

        mem::Memory *m_Memory;
        video::Video *m_Video;

        std::unique_ptr<OpcodeMap> m_OpcodeMap;
        std::array<byte, BYTES_IN_STACK> m_StackArray;
    }; // end of class Cpu

} // end of namespace cpu
} // end of namespace chu

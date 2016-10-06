#pragma once

#include <string>
#include "cpu.h"
#include "mem.h"
#include "util/macros.h"
#include "video.h"

namespace chu
{
namespace cpu
{
    enum class InstrType;
    class Cpu;

    class Instruction
    {
    public:
        Instruction();
        Instruction(const word opcode, Cpu *cpu, mem::Memory *mem, video::Video *video);

        void execute() const;
        std::string to_string() const;

        const InstrType type() const;

    private:
        InstrType m_Type;
        word m_Opcode;
        Cpu *m_Cpu;
        mem::Memory *m_Memory;
        video::Video *m_Video;
    };

    enum class InstrType
    {
        Sys, Cls, Ret, Call,
        ScdN, Scr, Scl, Exit,
        Low, High, DrwVV0,
        JpAddr, JpVAddr,
        SeVB, SeVV,
        SneVB, SneVV,
        LdHfV, LdRV, LdVR,
        LdVB, LdVV, LdIAddr,
        LdVDt, LdVK, LdDtV,
        LdStV, LdFV, LdBV,
        LdIV, LdVI,
        AddVB, AddVV,
        AddIV,
        SubVV, SubnVV,
        ShrV, ShlV,
        OrVV, AndVV, XorVV, 
        RndVB, DrwVVN,
        SkpV, SknpV,
        NOP, // no-op
    };
} // end of namespace cpu
} // end of namespace chu

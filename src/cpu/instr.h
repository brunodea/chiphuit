#pragma once

#include "util/macros.h"

namespace chu
{
namespace cpu
{
    enum class InstrType;

    class Instruction
    {
    public:
        Instruction();
        Instruction(const word &opcode);

        inline
        const InstrType &type() const noexcept;

    private:
        InstrType m_Type;
        word m_Opcode;
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

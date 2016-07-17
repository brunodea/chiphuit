#include "instr.h"

#include <string>

using namespace chu::cpu;

Instruction::Instruction()
    : m_Type(InstrType::NOP), m_Opcode(0)
{}

Instruction::Instruction(const word &opcode)
    : m_Opcode(opcode)
{
    for (int i = 0; i < NUMBER_OF_INSTRS; ++i)
    {
        switch (i)
        {
        case 0x0000 ... 0x00BF:
            m_Type = InstrType::Sys;
            break;
        case 0x00C0 ... 0x00CF:
            m_Type = InstrType::ScdN;
            break;
        case 0x00E0:
            m_Type = InstrType::Cls;
            break;
        case 0x00EE:
            m_Type = InstrType::Ret;
            break;
        case 0x00FB:
            m_Type = InstrType::Scr;
            break;
        case 0x00FC:
            m_Type = InstrType::Scl;
            break;
        case 0x00FD:
            m_Type = InstrType::Exit;
            break;
        case 0x00FE:
            m_Type = InstrType::Low;
            break;
        case 0x00FF:
            m_Type = InstrType::High;
            break;
        case 0x1000 ... 0x1FFF:
            m_Type = InstrType::JpAddr;
            break;
        case 0x2000 ... 0x2FFF:
            m_Type = InstrType::Call;
            break;
        case 0x3000 ... 0x3FFF:
            m_Type = InstrType::SeVB;
            break;
        case 0x4000 ... 0x4FFF:
            m_Type = InstrType::SneVB;
            break;
        case 0x5000 ... 0x5FFF:
            switch (opcode & 0b1)
            {
            case 0:
                m_Type = InstrType::SeVV;
                break;
            default:
                m_Type = InstrType::NOP;
                break;
            }
            break;
        case 0x6000 ... 0x6FFF:
            m_Type = InstrType::LdVB;
            break;
        case 0x7000 ... 0x7FFF:
            m_Type = InstrType::AddVB;
            break;
        case 0x8000 ... 0x8FFF:
            switch (opcode & 0b1)
            {
            case 0x0:
                m_Type = InstrType::LdVV;
                break;
            case 0x1:
                m_Type = InstrType::OrVV;
                break;
            case 0x2:
                m_Type = InstrType::AndVV;
                break;
            case 0x3:
                m_Type = InstrType::XorVV;
                break;
            case 0x4:
                m_Type = InstrType::AddVV;
                break;
            case 0x5:
                m_Type = InstrType::SubVV;
                break;
            case 0x6:
                m_Type = InstrType::ShrV;
                break;
            case 0x7:
                m_Type = InstrType::SubnVV;
                break;
            case 0xE:
                m_Type = InstrType::ShlV;
                break;
            default:
                m_Type = InstrType::NOP;
                break;
            }
            break;
        case 0x9000 ... 0x9FFF:
            switch (opcode & 0b1)
            {
            case 0:
                m_Type = InstrType::SneVV;
                break;
            default:
                m_Type = InstrType::NOP;
                break;
            }
            break;
        case 0xA000 ... 0xAFFF:
            m_Type = InstrType::LdIAddr;
            break;
        case 0xB000 ... 0xBFFF:
            m_Type = InstrType::JpVAddr;
            break;
        case 0xC000 ... 0xCFFF:
            m_Type = InstrType::RndVB;
            break;
        case 0xD000 ... 0xDFFF:
            switch (opcode & 0b1)
            {
            case 0:
                m_Type = InstrType::DrwVV0;
                break;
            default:
                m_Type = InstrType::DrwVVN;
                break;
            }
            break;
        case 0xE000 ... 0xEFFF:
            switch (opcode & 0b11)
            {
            case 0x9E:
                m_Type = InstrType::SkpV;
                break;
            case 0xA1:
                m_Type = InstrType::SknpV;
                break;
            default:
                m_Type = InstrType::NOP;
                break;
            }
            break;
        case 0xF000 ... 0xFFFF:
            switch (opcode &0b11)
            {
            case 0x07:
                m_Type = InstrType::LdVDt;
                break;
            case 0x0A:
                m_Type = InstrType::LdVK;
                break;
            case 0x15:
                m_Type = InstrType::LdDtV;
                break;
            case 0x18:
                m_Type = InstrType::LdStV;
                break;
            case 0x1E:
                m_Type = InstrType::AddIV;
                break;
            case 0x29:
                m_Type = InstrType::LdFV;
                break;
            case 0x30:
                m_Type = InstrType::LdHfV;
                break;
            case 0x33:
                m_Type = InstrType::LdBV;
                break;
            case 0x55:
                m_Type = InstrType::LdIV;
                break;
            case 0x65:
                m_Type = InstrType::LdVI;
                break;
            case 0x75:
                m_Type = InstrType::LdRV;
                break;
            case 0x85:
                m_Type = InstrType::LdVR;
                break;
            default:
                m_Type = InstrType::NOP;
                break;
            }
            break;
        default:
            m_Type = InstrType::NOP;
            break;
        }
    }
}


const InstrType &Instruction::type() const noexcept
{
    return m_Type;
}

std::string Instruction::to_string() const noexcept
{
    std::string result("");
    switch (m_Type)
    {
        case InstrType::Sys:
            break;
        case InstrType::ScdN:
            break;
        case InstrType::Cls:
            break;
        case InstrType::Ret:
            break;
        case InstrType::Scr:
            break;
        case InstrType::Scl:
            break;
        case InstrType::Exit:
            break;
        case InstrType::Low:
            break;
        case InstrType::High:
            break;
        case InstrType::JpAddr:
            break;
        case InstrType::Call:
            break;
        case InstrType::SeVB:
            break;
        case InstrType::SneVB:
            break;
        case InstrType::SeVV:
            break;
        case InstrType::LdVB:
            break;
        case InstrType::AddVB:
            break;
        case InstrType::LdVV:
            break;
        case InstrType::OrVV:
            break;
        case InstrType::AndVV:
            break;
        case InstrType::XorVV:
            break;
        case InstrType::AddVV:
            break;
        case InstrType::SubVV:
            break;
        case InstrType::ShrV:
            break;
        case InstrType::SubnVV:
            break;
        case InstrType::ShlV:
            break;
        case InstrType::SneVV:
            break;
        case InstrType::LdIAddr:
            break;
        case InstrType::JpVAddr:
            break;
        case InstrType::RndVB:
            break;
        case InstrType::DrwVV0:
            break;
        case InstrType::DrwVVN:
            break;
        case InstrType::SkpV:
            break;
        case InstrType::SknpV:
            break;
        case InstrType::LdVDt:
            break;
        case InstrType::LdVK:
            break;
        case InstrType::LdDtV:
            break;
        case InstrType::LdStV:
            break;
        case InstrType::AddIV:
            break;
        case InstrType::LdFV:
            break;
        case InstrType::LdHfV:
            break;
        case InstrType::LdBV:
            break;
        case InstrType::LdIV:
            break;
        case InstrType::LdVI:
            break;
        case InstrType::LdRV:
            break;
        case InstrType::LdVR:
            break;
        default:
            break;
    }

    return result;
}

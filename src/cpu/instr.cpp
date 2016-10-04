#include "instr.h"

#include <string>
#include <sstream>
#include <iostream> // std::hex
#include <random>
#include <iomanip> // std::setfill // std::setw

#include "mem.h"

using namespace chu::cpu;
using namespace chu::mem;
using namespace chu::video;

Instruction::Instruction()
    : m_Type(InstrType::NOP), m_Opcode(0), m_Cpu(nullptr), m_Memory(nullptr), m_Video(nullptr)
{}

Instruction::Instruction(const word opcode, Cpu *cpu, Memory *mem, Video *video)
    : m_Opcode(opcode), m_Cpu(cpu), m_Memory(mem), m_Video(video)
{
    switch (opcode)
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


const InstrType &Instruction::type() const noexcept
{
    return m_Type;
}

std::string Instruction::to_string() const noexcept
{
    std::stringstream ss;
    enum class ElemOrder
    {
        VVNib, VV, VB, BV, V, Addr, Nibble, None
    };

    ss << "[0x" << std::hex << m_Opcode << "] ";
    auto order = ElemOrder::None;
    switch (m_Type)
    {
        case InstrType::Sys:
            ss << "SYS";
            order = ElemOrder::Addr;
            break;
        case InstrType::ScdN:
            ss << "SCD";
            break;
        case InstrType::Cls:
            ss << "CLS";
            break;
        case InstrType::Ret:
            ss << "RET";
            break;
        case InstrType::Scr:
            ss << "SCR";
            break;
        case InstrType::Scl:
            ss << "SCL";
            break;
        case InstrType::Exit:
            ss << "EXIT";
            break;
        case InstrType::Low:
            ss << "LOW";
            break;
        case InstrType::High:
            ss << "HIGH";
            break;
        case InstrType::JpAddr:
            ss << "JP";
            order = ElemOrder::Addr;
            break;
        case InstrType::Call:
            ss << "Call";
            order = ElemOrder::Addr;
            break;
        case InstrType::SeVB:
            ss << "SE";
            order = ElemOrder::VB;
            break;
        case InstrType::SneVB:
            ss << "SNE";
            order = ElemOrder::VB;
            break;
        case InstrType::SeVV:
            ss << "SE";
            order = ElemOrder::VV;
            break;
        case InstrType::LdVB:
            ss << "LD";
            order = ElemOrder::VB;
            break;
        case InstrType::AddVB:
            ss << "ADD";
            order = ElemOrder::VB;
            break;
        case InstrType::LdVV:
            ss << "LD";
            order = ElemOrder::VV;
            break;
        case InstrType::OrVV:
            ss << "OR";
            order = ElemOrder::VV;
            break;
        case InstrType::AndVV:
            ss << "AND";
            order = ElemOrder::VV;
            break;
        case InstrType::XorVV:
            ss << "XOR";
            order = ElemOrder::VV;
            break;
        case InstrType::AddVV:
            ss << "ADD";
            order = ElemOrder::VV;
            break;
        case InstrType::SubVV:
            ss << "SUB";
            order = ElemOrder::VV;
            break;
        case InstrType::ShrV:
            ss << "SHR";
            order = ElemOrder::V;
            break;
        case InstrType::SubnVV:
            ss << "SUBN";
            order = ElemOrder::VV;
            break;
        case InstrType::ShlV:
            ss << "SHL";
            order = ElemOrder::V;
            break;
        case InstrType::SneVV:
            ss << "SNE";
            order = ElemOrder::VV;
            break;
        case InstrType::LdIAddr:
            ss << "LDI";
            order = ElemOrder::Addr;
            break;
        case InstrType::JpVAddr:
            ss << "JPV0";
            order = ElemOrder::Addr;
            break;
        case InstrType::RndVB:
            ss << "RND";
            order = ElemOrder::VB;
            break;
        case InstrType::DrwVV0:
        case InstrType::DrwVVN:
            ss << "DRW";
            order = ElemOrder::VVNib;
            break;
        case InstrType::SkpV:
            ss << "SKP";
            order = ElemOrder::V;
            break;
        case InstrType::SknpV:
            ss << "SKNP";
            order = ElemOrder::V;
            break;
        case InstrType::LdVDt:
            ss << "LDVDT";
            order = ElemOrder::V;
            break;
        case InstrType::LdVK:
            ss << "LDK";
            order = ElemOrder::V;
            break;
        case InstrType::LdDtV:
            ss << "LDDTV";
            order = ElemOrder::V;
            break;
        case InstrType::LdStV:
            ss << "LDST";
            order = ElemOrder::V;
            break;
        case InstrType::AddIV:
            ss << "ADDI";
            order = ElemOrder::V;
            break;
        case InstrType::LdFV:
            ss << "LDF";
            order = ElemOrder::V;
            break;
        case InstrType::LdHfV:
            ss << "LDHF";
            order = ElemOrder::V;
            break;
        case InstrType::LdBV:
            ss << "LDB";
            order = ElemOrder::V;
            break;
        case InstrType::LdIV:
            ss << "LD[I]V";
            order = ElemOrder::V;
            break;
        case InstrType::LdVI:
            ss << "LDV[I]";
            order = ElemOrder::V;
            break;
        case InstrType::LdRV:
            ss << "LDRV";
            order = ElemOrder::V;
            break;
        case InstrType::LdVR:
            ss << "LDVR";
            order = ElemOrder::V;
            break;
        default:
            break;
    }

    switch (order)
    {
    case ElemOrder::Addr:
        ss << " 0x" << std::setfill('0') << std::setw(2) << std::hex << (m_Opcode & 0x0FFF);
        break;
    case ElemOrder::Nibble:
        ss << " 0x" << std::setfill('0') << std::setw(2) << std::hex << (m_Opcode & 0x000F);
        break;
    case ElemOrder::VB:
        ss <<
            " V"  << std::hex << ((m_Opcode >> 8) & 0x000F) <<
            ",0x" << std::setfill('0') << std::setw(2) << std::hex << (m_Opcode & 0x00FF);
        break;
    case ElemOrder::BV:
        ss <<
            " 0x" << std::setfill('0') << std::setw(2) << std::hex << (m_Opcode & 0x00FF) <<
            ",V"  << std::hex << ((m_Opcode >> 8) & 0x000F);
        break;
    case ElemOrder::VV:
        ss <<
            " V" << std::hex << ((m_Opcode >> 4 ) & 0x000F) <<
            ",V" << std::hex << ((m_Opcode >> 8) & 0x000F);
        break;
    case ElemOrder::VVNib:
        ss <<
            " V"  << std::hex << ((m_Opcode >> 4 ) & 0x000F) <<
            ",V"  << std::hex << ((m_Opcode >> 8) & 0x000F) <<
            ",0x" << std::setfill('0') << std::setw(2) << std::hex << (m_Opcode & 0x000F);
        break;
    case ElemOrder::V:
        ss <<
            " V" << std::hex << ((m_Opcode >> 8) & 0x000F);
        break;
    default:
        break;
    }

    return ss.str();
}

void Instruction::execute() const
{
    auto addr = m_Opcode & 0x0FFF;
    auto lreg = (m_Opcode >> 8) & 0x000F;
    auto rreg = (m_Opcode >> 4) & 0x000F;
    auto imme = m_Opcode & 0x00FF;

    auto *x = &m_Cpu->m_GenRegs[lreg];
    auto *y = &m_Cpu->m_GenRegs[rreg];

    switch (m_Type)
    {
    case InstrType::Sys:
        // do nothing instead?
        m_Cpu->m_PC = addr;
        break;
    case InstrType::ScdN:
        break;
    case InstrType::Cls:
        break;
    case InstrType::Ret:
        m_Cpu->m_PC = m_Cpu->pop_stack_word();
        goto bypass_pc_increment;
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
        m_Cpu->m_PC = addr;
        goto bypass_pc_increment;
        break;
    case InstrType::Call:
        m_Cpu->push_stack_word(m_Cpu->m_PC);
        m_Cpu->m_PC = addr;
        goto bypass_pc_increment;
        break;
    case InstrType::SeVB:
        if (*x == imme) m_Cpu->m_PC++;
        break;
    case InstrType::SneVB:
        if (*x != imme) m_Cpu->m_PC++;
        break;
    case InstrType::SeVV:
        if (*x == *y) m_Cpu->m_PC++;
        break;
    case InstrType::LdVB:
        *x = imme;
        break;
    case InstrType::AddVB:
        *x += imme;
        break;
    case InstrType::LdVV:
        *x = *y;
        break;
    case InstrType::OrVV:
        *x |= *y;
        break;
    case InstrType::AndVV:
        *x &= *y;
        break;
    case InstrType::XorVV:
        *x ^= *y;
        break;
    case InstrType::AddVV:
        {
            auto sum = static_cast<word>(*x) + static_cast<word>(*y);
            m_Cpu->m_FlagReg = sum > 0xFF ? 1 : 0;
            *x = static_cast<byte>(sum);
        }
        break;
    case InstrType::SubVV:
        m_Cpu->m_FlagReg = *x > *y ? 1 : 0;
        *x -= *y;
        break;
    case InstrType::ShrV:
        m_Cpu->m_FlagReg = (*x & 0b1) == 1 ? 1 : 0;
        *x >>= 1;
        break;
    case InstrType::SubnVV:
        m_Cpu->m_FlagReg = *y > *x ? 1 : 0;
        *x = *y - *x;
        break;
    case InstrType::ShlV:
        m_Cpu->m_FlagReg = (*x & 0b10000000) == 1 ? 1 : 0;
        *x <<= 1;
        break;
    case InstrType::SneVV:
        if (*x != *y) m_Cpu->m_PC++;
        break;
    case InstrType::LdIAddr:
        m_Cpu->m_MemReg = addr;
        break;
    case InstrType::JpVAddr:
        m_Cpu->m_PC = addr + m_Cpu->m_GenRegs[0];
        goto bypass_pc_increment;
        break;
    case InstrType::RndVB:
        {
            std::default_random_engine gen;
            std::uniform_int_distribution<byte> dist(0x00, 0xFF);
            *x = dist(gen) & imme;
        }
        break;
    case InstrType::DrwVV0:
    case InstrType::DrwVVN:
        {
            std::cout << "DRWVVN" << std::endl;
            bool set_vf = false;
            imme = imme == 0 ? 1 : imme;
            for (auto i = 0; i < imme; i++)
            {
                auto sprite_byte = m_Memory->read(m_Cpu->m_MemReg + i);
                set_vf = m_Video->set_byte(sprite_byte, *x, *y);
            }
            m_Cpu->m_FlagReg = set_vf ? 1 : 0;
        }
        break;
    case InstrType::SkpV:
        break;
    case InstrType::SknpV:
        break;
    case InstrType::LdVDt:
        *x = m_Cpu->m_DelayReg;
        break;
    case InstrType::LdVK:
        break;
    case InstrType::LdDtV:
        m_Cpu->m_DelayReg = *x;
        break;
    case InstrType::LdStV:
        m_Cpu->m_SoundReg = *x;
        break;
    case InstrType::AddIV:
        m_Cpu->m_MemReg += *x;
        break;
    case InstrType::LdFV:
        break;
    case InstrType::LdHfV:
        break;
    case InstrType::LdBV:
        {
            auto c = *x / 100;
            auto d = ((*x / 10) % 10);
            auto u = *x - (c * 100) + (d * 10);
            m_Memory->write(m_Cpu->m_MemReg, c);
            m_Memory->write(m_Cpu->m_MemReg + 1, d);
            m_Memory->write(m_Cpu->m_MemReg + 2, u);
        }
        break;
    case InstrType::LdIV:
        {
            int i;
            for (i = 0; i < lreg; ++i)
            {
                auto val = i == 16 ? m_Cpu->m_FlagReg : m_Cpu->m_GenRegs[i];
                m_Memory->write(m_Cpu->m_MemReg + i, val);
            }
            m_Cpu->m_MemReg += i; // TODO: make sure this should be done
        }
        break;
    case InstrType::LdVI:
        {
            int i;
            for (i = 0; i < lreg; ++i)
            {
                auto val = m_Memory->read(m_Cpu->m_MemReg + i);
                if (i == 16)
                    m_Cpu->m_FlagReg = val;
                else
                    m_Cpu->m_GenRegs[i] = val;
            }
            m_Cpu->m_MemReg += i; // TODO: make sure this should be done
        }
        break;
    case InstrType::LdRV:
        break;
    case InstrType::LdVR:
        break;
    default:
        break;
    }

    m_Cpu->m_PC += 2;
bypass_pc_increment:
    ; // do nothing.
}

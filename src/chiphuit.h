#pragma once

#include <memory>
#include <vector>

#include "cpu.h"
#include "mem.h"
#include "instr.h"
#include "macros.h"
#include "video.h"

namespace chu
{
    class ChipHuit
    {
    public:
        ChipHuit(const std::vector<byte> &rom);

        void start();
    private:
        std::unique_ptr<cpu::Cpu> m_Cpu;
        std::unique_ptr<mem::Memory> m_Memory;
        std::unique_ptr<video::Video> m_Video;
    };
} // end of namespace chu

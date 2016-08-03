#include "chiphuit.h"

#include "mem.h"
#include "macros.h"

#include <SDL2/SDL.h>

using namespace chu;

ChipHuit::ChipHuit(const std::vector<byte> &rom)
{
    m_Memory = std::make_unique<mem::Memory>();
    m_Memory->load_rom(rom);

#ifndef NDEBUG
    m_Memory->print_chunk(MEMORY_ROM_START_ADDR, MEMORY_ROM_START_ADDR+rom.size());
#endif

    m_Cpu = std::make_unique<cpu::Cpu>(m_Memory.get());
    m_Video = std::make_unique<video::Video>();
}

void ChipHuit::start()
{
    const unsigned int delta = 5;
    m_Video->setup(WINDOW_WIDTH*delta, WINDOW_HEIGHT*delta);

    while (true)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                goto stop;
        }
        m_Cpu->step();
    }

stop:
    ;
}

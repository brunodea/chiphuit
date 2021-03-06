#include "chiphuit.h"

#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>

#ifndef NDEBUG
#include "debugger.h"
#endif

using namespace chu;

ChipHuit::ChipHuit(const std::vector<byte> &rom)
{
    m_Memory = std::make_unique<mem::Memory>();
    m_Memory->load_rom(rom);

    m_Video = std::make_unique<video::Video>();
    m_Cpu = std::make_unique<cpu::Cpu>(m_Memory.get(), m_Video.get());
}

void ChipHuit::start()
{
    m_Video->setup(10);

    auto start = std::chrono::steady_clock::now();
#ifndef NDEBUG
    dbg::Debugger debugger;
    std::cout << ">>>>>>>> Debug Mode <<<<<<<<" << std::endl;
    debugger.print_help();
#endif
    do
    {
 #ifndef NDEBUG
        auto cmd = debugger.run(*m_Cpu, *m_Memory);
        switch (cmd.type())
        {
        case dbg::CommandType::QUIT:
            goto stop;
            break;
        default:
            break;
        }
#endif
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                goto stop;
        }
        auto instr = m_Cpu->step();
        switch (instr.type())
        {
            case cpu::InstrType::Cls:
                m_Video->clear_screen();
                break;
            default:
                break;
        }

        if ((std::chrono::steady_clock::now() - start).count() >= 60)
        {
            // 60 hz
            start = std::chrono::steady_clock::now();
            m_Cpu->update_delay_register();
        }
        m_Video->update();

   } while(true);

stop:
    ;
}

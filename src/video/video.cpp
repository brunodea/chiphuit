#include "video.h"
#include <stdexcept>
#include <SDL2/SDL.h>

using namespace chu::video;

Video::Video()
    : m_Window(nullptr), m_Surface(nullptr)
{
}

Video::~Video()
{
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Video::setup(const unsigned int width, const unsigned int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw std::runtime_error("Couldn't initialize the SDL video.");
    }
    else
    {
        m_Window = SDL_CreateWindow("ChipHuit", SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (m_Window == nullptr)
        {
            throw std::runtime_error("Couldn't create window.");
        }
        else
        {
            m_Surface = SDL_GetWindowSurface(m_Window);
            clear_screen();
        }
    }
}

void Video::clear_screen()
{
    SDL_FillRect(m_Surface, nullptr, SDL_MapRGB(m_Surface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(m_Window);
}



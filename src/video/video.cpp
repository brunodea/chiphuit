#include "video.h"
#include <stdexcept>
#include <SDL2/SDL.h>
#include <algorithm>
#include <iostream>

#include "macros.h"

using namespace chu::video;

Video::Video()
    : m_Window(nullptr), m_Renderer(nullptr), m_Pixels{0}
{
}

Video::~Video()
{
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Video::setup(const unsigned int delta)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw std::runtime_error("Couldn't initialize the SDL video.");
    }
    else
    {
        m_Window = SDL_CreateWindow("ChipHuit", SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH*delta, WINDOW_HEIGHT*delta, SDL_WINDOW_SHOWN);
        if (m_Window == nullptr)
        {
            throw std::runtime_error("Couldn't create window.");
        }
        else
        {
            m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
            SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0x00);
//            clear_screen();
        }
    }
}

void Video::clear_screen()
{
    memset(m_Pixels, 0, sizeof m_Pixels);
}

bool Video::set_byte(const byte b, const unsigned int x, const unsigned int y)
{
    //std::cout << std::flush << x << ',' << y << std::endl;
    auto pb = pixel_byte(x, y);
    auto old_byte = m_Pixels[pb];
    auto res = b^old_byte;

    m_Pixels[pb] = res;

    return (b & res) != b;
}

unsigned int Video::pixel_byte(const unsigned int x, const unsigned int y) const
{
    return ((BYTES_IN_WIDTH * y) % BYTES_IN_HEIGHT)+ ((x / BITS_IN_BYTE) % BYTES_IN_WIDTH);
}

void Video::update()
{
    auto surface = SDL_CreateRGBSurfaceFrom((void*)m_Pixels,
                WINDOW_WIDTH,
                WINDOW_HEIGHT,
                1,          // bits per pixel = 24
                BYTES_IN_WIDTH,  // pitch
                0,              // red mask
                0,              // green mask
                0,              // blue mask
                0);                    // alpha mask (none)
    auto texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderClear(m_Renderer);
    SDL_RenderCopy(m_Renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(m_Renderer);
    SDL_DestroyTexture(texture);
}

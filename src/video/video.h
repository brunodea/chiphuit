#pragma once

#include <SDL2/SDL.h>
#include "macros.h"

namespace chu
{
namespace video
{
    class Video
    {
    public:
        Video();
        ~Video();

        void setup(const unsigned int delta);
        void clear_screen();
        void update();
        // returns true if any pixel is erased.
        bool set_byte(const byte b, const unsigned int x, const unsigned int y);
        bool pixel(const unsigned int x, const unsigned int y) const;

    private:
        SDL_Window *m_Window;
        SDL_Renderer *m_Renderer;

        byte m_Pixels[BYTES_IN_SCREEN];

    private:
        unsigned int pixel_byte(const unsigned int x, const unsigned int y) const;
    };
} // end of namespace video
} // end of namespace chu

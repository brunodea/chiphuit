#pragma once

#include <SDL2/SDL.h>

namespace chu
{
namespace video
{
    class Video
    {
    public:
        Video();
        ~Video();

        void setup(const unsigned int width, const unsigned int height);
        void clear_screen();

    private:
        SDL_Window *m_Window;
        SDL_Surface *m_Surface;
    };
} // end of namespace video
} // end of namespace chu

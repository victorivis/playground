#pragma once
#include <SDL2/SDL.h>

class Audio{
    private:
        SDL_AudioSpec spec;
        Uint8 *audio_buffer;
        Uint32 audio_length;
        SDL_AudioStream *stream;

    public:
        Audio();
        ~Audio();
        void runSound(char caminho[]);
};
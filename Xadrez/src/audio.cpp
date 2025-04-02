#include "audio.h"
#include <cstdio>

Audio::Audio(){
    stream = SDL_NewAudioStream(AUDIO_S16, 1, 22050, AUDIO_F32, 2, 48000);
    if (stream == NULL) {
        printf("Erro ao criar stream: %s\n", SDL_GetError());
    }
}

void Audio::runSound(char caminho[]){
    if(audio_length <= 0){
        SDL_FreeWAV(audio_buffer);
        if(SDL_LoadWAV("assets/sound.wav", &spec, &audio_buffer, &audio_length) != NULL){
            SDL_PauseAudio(0);
        }
    }
}

Audio::~Audio(){
    SDL_FreeWAV(audio_buffer);
    SDL_FreeAudioStream(stream);
}
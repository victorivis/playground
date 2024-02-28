#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

// Tamanho do buffer de áudio
const int BUFFER_SIZE = 4096;

// Frequência do sinal sonoro
int FREQUENCY = 440;

// Função para preencher o buffer de áudio com um sinal sonoro
void generateSound(Uint8 *buffer, int length) {
    for (int i = 0; i < length; i++) {
        // Gerando uma onda senoidal simples para produzir um som
        float sample = sin(2.0 * M_PI * FREQUENCY * i / 44100.0);

        // Convertendo o valor da amostra para o formato de 8 bits sem sinal
        buffer[i] = (Uint8)((sample + 1.0) * 127.5);
    }
}

// Função para reproduzir um sinal sonoro usando SDL2
void playSound() {
    // Inicializando o SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Erro ao inicializar o SDL: %s\n", SDL_GetError());
        return;
    }

    // Configurando as especificações do áudio
    SDL_AudioSpec audioSpec;
    audioSpec.freq = 44100;
    audioSpec.format = AUDIO_U8;
    audioSpec.channels = 1;
    audioSpec.samples = BUFFER_SIZE;
    audioSpec.callback = NULL;

    // Abertura do dispositivo de áudio
    if (SDL_OpenAudio(&audioSpec, NULL) < 0) {
        printf("Erro ao abrir o dispositivo de áudio: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    // Alocando o buffer de áudio
    Uint8 buffer[BUFFER_SIZE];

    // Preenchendo o buffer de áudio
    generateSound(buffer, BUFFER_SIZE);

    // Reproduzindo o som
    SDL_QueueAudio(1, buffer, BUFFER_SIZE);
    SDL_PauseAudio(0);

    // Aguardando o término da reprodução
    SDL_Delay(50);

    // Fechando o dispositivo de áudio e finalizando o SDL
    SDL_CloseAudio();
    SDL_Quit();
}

/*
int main() {
    // Chamando a função para produzir e reproduzir o sinal sonoro
    playSound();

    return 0;
}
*/

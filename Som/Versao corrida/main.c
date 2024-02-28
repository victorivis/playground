#include <SDL2/SDL.h>
#include <stdio.h>
//#include <math.h>

// Tamanho do buffer de áudio
const int BUFFER_SIZE = 4096;

// Frequência do sinal sonoro
const int FREQUENCY = 440;

// Função para preencher o buffer de áudio
void fillAudioBuffer(Uint8 *buffer, int length) {
    for (int i = 0; i < length; i++) {
        // Gerando uma onda senoidal simples para produzir um som
        float sample = sin(2.0 * M_PI * FREQUENCY * i / 44100.0);

        // Convertendo o valor da amostra para o formato de 8 bits sem sinal
        buffer[i] = (Uint8)((sample + 1.0) * 127.5);
    }
}

int main() {
    // Inicializando o SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Erro ao inicializar o SDL: %s\n", SDL_GetError());
        return 1;
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
        return 1;
    }

    // Alocando o buffer de áudio
    Uint8 buffer[BUFFER_SIZE];

    // Preenchendo o buffer de áudio
    fillAudioBuffer(buffer, BUFFER_SIZE);

    // Reproduzindo o som
    SDL_QueueAudio(1, buffer, BUFFER_SIZE);
    SDL_PauseAudio(0);

    // Aguardando o término da reprodução
    SDL_Delay(1000);

    // Fechando o dispositivo de áudio e finalizando o SDL
    SDL_CloseAudio();
    SDL_Quit();

    return 0;
}


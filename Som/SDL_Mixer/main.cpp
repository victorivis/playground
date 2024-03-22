#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

int WIDTH = 1000;
int HEIGHT = 600;

std::vector<Mix_Chunk*> sounds;
std::vector<Mix_Music*> music;

int loadMusic(const char* filename) {
	Mix_Music *m = NULL;
	m = Mix_LoadMUS(filename);
	if(m == NULL) {
		printf("Failed to load music. SDL_Mixer error: %s\n", Mix_GetError());
		return -1;
	}
	music.push_back(m);
	return music.size()-1;
}

int loadSound(const char* filename) {
	Mix_Chunk *m = NULL;
	m = Mix_LoadWAV(filename);
	if(m == NULL) {
		printf("Failed to load music. SDL_Mixer error: %s\n", Mix_GetError());
		return -1;
	}
	sounds.push_back(m);
	return sounds.size()-1;
}

int volume;
void setVolume(int v) {
	volume = (MIX_MAX_VOLUME * v) / 100;
}

int playMusic(int m) {
	if(Mix_PlayingMusic() == 0) {
		Mix_Volume(1, volume);
		Mix_PlayMusic(music[m], -1);
	}
	return 0;
}

int playSound(int s) {
	Mix_Volume(-1, volume);
        Mix_PlayChannel(-1, sounds[s], 0);
	return 0;
}

int initMixer() {
	Mix_Init(MIX_INIT_MP3);
	SDL_Init(SDL_INIT_AUDIO);
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_Mixer couldnt init. Err: %s\n", Mix_GetError());
		return -1;
	}
	setVolume(1);
	return 0;
}

void quitMixer() {
	for(int s=0; s<sounds.size(); s++) {
		Mix_FreeChunk(sounds[s]);
		sounds[s]=NULL;
	}
	for(int s=0; s<music.size(); s++) {
		Mix_FreeMusic(music[s]);
		music[s]=NULL;
	}
	Mix_Quit();
}

void togglePlay() {
	if(Mix_PausedMusic() == 1) {
		Mix_ResumeMusic();
	} else {
		Mix_PauseMusic();
	}
}

int main(int argc, char* argv[]) {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;  

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Sons Shockantes!",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
							  WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	initMixer();
	int sound = loadSound("assets/sound.wav");
	int song = loadMusic("assets/zero.mp3");
	playMusic(song);
	
	bool rodar=true;
	SDL_Event evento;
	while(rodar){
		while(SDL_PollEvent(&evento)){
			if(evento.type == SDL_QUIT) rodar=0;

			else if(evento.type == SDL_KEYDOWN){
				switch(evento.key.keysym.sym){
					case SDLK_ESCAPE:
						rodar=0;
						break;

					case 'q': playSound(sound);	break;
					case 'p': togglePlay(); break;
				}
			}
		}
	}
	quitMixer();
	
	//Liberando memoria
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

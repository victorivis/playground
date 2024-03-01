#include <SDL2/SDL.h>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

struct trio{
	int r;
	int g;
	int b;
};

const int WIDTH = 1080, HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int main(int argc, char* argv[]) {
	//Criar Janela
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Snake",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
							  WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_Event evento;
	int rodar=1;
	short int VEL=TAM_COBRA;
	short int direcao = -1;
	int num_segmentos=1;

	//Jogo propriamente dito
	while(rodar){
		while(SDL_PollEvent(&evento)){
			sair_pausa:
			if(evento.type == SDL_QUIT) rodar=0;

			else if(evento.type == SDL_KEYDOWN){
				printf("%d\n", evento.key.keysym.sym);
				switch(evento.key.keysym.sym){
					case SDLK_ESCAPE:
						rodar=0;
						break;

					//pausa
					case 'p': do{
						SDL_PollEvent(&evento);
						} while(evento.type!=SDL_KEYDOWN);
						goto sair_pausa;
						break;
				}
			}
		}

		//Plano de Fundo
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);

		SDL_Delay(100);
	}

	return 0;
}
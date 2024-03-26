#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include "menu.h"

using namespace std;

const int WIDTH = 1080, HEIGHT = 600;
float TICKS = 100;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Menu inicial = Menu(WIDTH, HEIGHT);


int main(int argc, char* argv[]) {
	SDL_Event evento;
	int rodar=1;

	//Criar Janela
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Menus",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
							  WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	//Jogo propriamente dito
	while(rodar){
		while(SDL_PollEvent(&evento)){
			sair_pausa:
			if(evento.type == SDL_QUIT) rodar=0;

			else if(evento.type == SDL_KEYDOWN){
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
					
					case '=': TICKS/=2; break;
					case '-': TICKS*=2; break;
				}
			}
		}

		//Plano de Fundo
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderClear(renderer);

		//inicial.inicializar(&renderer, {"Continuar", "Sair"}, "Sans.ttf", 64);
		if(inicial.menu_generico(&renderer, {"Continuar", "Sair"}, "Sans.ttf", 64) == Sair){
			rodar=0;
		}
		//inicial.finalizar();

		SDL_RenderPresent(renderer);

		SDL_Delay((Uint32) TICKS);
	}
	
	//Liberando memoria
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

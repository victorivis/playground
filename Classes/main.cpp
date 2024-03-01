#include <SDL2/SDL.h>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "player.h"

using namespace std;

const int WIDTH = 1080, HEIGHT = 600;
float TICKS = 100;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

const int NUM_PLAYERS=2;
const int NUM_SOMBRAS=2;

int main(int argc, char* argv[]) {
	//Variaveis de controle e configuracao
	Player sombra[] = {
		{WIDTH, HEIGHT, {SDLK_UP, SDLK_DOWN, SDLK_RIGHT, SDLK_LEFT, 'i', 'k', 'l', 'j'}, {255, 255, 255}},
		{WIDTH, HEIGHT, {'w', 's', 'd', 'a', 'i', 'k', 'l', 'j'}, {255,120,160}},
		{WIDTH, HEIGHT, {'i', 'k', 'l', 'j', 'i', 'k', 'l', 'j'}, {255,120,160}},
	};

	Player p[] = {
		{WIDTH, HEIGHT, {SDLK_UP, SDLK_DOWN, SDLK_RIGHT, SDLK_LEFT}, {0, 0, 0}},
		{WIDTH, HEIGHT, {'w', 's', 'd', 'a'}, {0, 0, 200}},
		{WIDTH, HEIGHT, {'i', 'k', 'l', 'j'}, {0, 200, 0}},
	};

	int max_maca=20, minimo_sorteio=10;
	Maca myApple{WIDTH, HEIGHT, 2*p[0].TAM_COBRA, max_maca, minimo_sorteio};
	myApple.sortear_macas(true);
	SDL_Event evento;
	int rodar=1;

	//Criar Janela
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Snake",
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

					default:
						for(int i=0; i<NUM_SOMBRAS; i++){
							sombra[i].executar_controles(evento.key.keysym.sym);
						}
						
						for(int i=0; i<NUM_PLAYERS; i++){
							p[i].executar_controles(evento.key.keysym.sym);
						}
				}
			}
		}
		//Mover cabeca
		for(int i=0; i<NUM_PLAYERS; i++){
			p[i].mover_cobra(p[i].direcao);
		}

		for(int i=0; i<NUM_SOMBRAS; i++){
			sombra[i].mover_cobra(sombra[i].direcao);
		}

		//Colisao macas
		for(int i=0; i<NUM_PLAYERS; i++){
			myApple.colisao_macas(p[i]);
		}

		for(int i=0; i<NUM_SOMBRAS; i++){
			myApple.colisao_macas(sombra[i]);
		}
		
		//Colisao minhoca
		for(int i=0; i<NUM_PLAYERS; i++){
			for(int j=0; j<NUM_PLAYERS; j++){
				p[i].colisao_cobra(p[j].segmentos_cobra);
			}
		}
		
		for(int i=0; i<NUM_SOMBRAS; i++){
			for(int j=0; j<NUM_SOMBRAS; j++){
				sombra[i].colisao_cobra(sombra[i].segmentos_cobra);
			}
		}

		//Mover cobra
		for(int i=0; i<NUM_PLAYERS; i++){
			p[i].atualizar_posicoes();
		}

		for(int i=0; i<NUM_SOMBRAS; i++){
			sombra[i].atualizar_posicoes();
		}

		//Plano de Fundo
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderClear(renderer);

		//Desenhar macas
		myApple.desenhar_macas(&renderer, {255, 0, 0});

		//Desenhar a minhoca
		for(int i=0; i<NUM_PLAYERS; i++){
			p[i].desenhar_cobra(&renderer);
		}

		for(int i=0; i<NUM_SOMBRAS; i++){
			sombra[i].desenhar_cobra(&renderer);
		}

		SDL_RenderPresent(renderer);

		SDL_Delay((Uint32) TICKS);
	}

	return 0;
}
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

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

short minimo_sorteio=1;
int TAM_COBRA = 10;

int main(int argc, char* argv[]) {
	//Variaveis de controle e configuracao
	Player p1{WIDTH, HEIGHT, {SDLK_UP, SDLK_DOWN, SDLK_RIGHT, SDLK_LEFT}, {255, 255, 255}};
	Player p2{WIDTH, HEIGHT, {'w', 's', 'd', 'a'}, {0, 0, 0}};

	Maca myApple{WIDTH, HEIGHT, 10, 20, 0};
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
					default:
						p1.executar_controles(evento.key.keysym.sym);
						p2.executar_controles(evento.key.keysym.sym);
				}
			}
		}
		//Mover cabeca
		p1.mover_cobra(p1.direcao);
		p2.mover_cobra(p2.direcao);

		//Colisao macas
		myApple.colisao_macas(p1);
		myApple.colisao_macas(p2);

		//Colisao minhoca
		p1.colisao_cobra(p1.segmentos_cobra);
		p1.colisao_cobra(p2.segmentos_cobra);

		p2.colisao_cobra(p1.segmentos_cobra);
		p2.colisao_cobra(p2.segmentos_cobra);

		//Mover cobra
		p1.atualizar_posicoes();
		p2.atualizar_posicoes();

		//Plano de Fundo
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderClear(renderer);

		//Desenhar macas
		myApple.desenhar_macas(&renderer, {255, 0, 0});

		//Desenhar a minhoca
		p1.desenhar_cobra(&renderer);
		p2.desenhar_cobra(&renderer);

		SDL_RenderPresent(renderer);

		SDL_Delay(100);
	}

	return 0;
}

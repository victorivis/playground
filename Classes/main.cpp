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

int TAM_COBRA=10;
short frequencia_maca=20;
short total_macas=frequencia_maca;
short minimo_sorteio=1;
bool cobra_colorida=0;

void sortear_macas(vector<SDL_Rect>& macas, bool primeiro_sorteio=false){
	for_each(macas.begin(), macas.end(), [&](auto& rect_maca){
		if(rect_maca.x < 0 || primeiro_sorteio){
			rect_maca.x = rand()%(WIDTH/TAM_COBRA)*TAM_COBRA;
			rect_maca.y = rand()%(HEIGHT/TAM_COBRA)*TAM_COBRA;
			if(primeiro_sorteio){
				rect_maca.w = TAM_COBRA;
				rect_maca.h = TAM_COBRA;
			}
		}
	});
}

void colorir_cobra(vector<trio>& cores){
	for_each(cores.begin(), cores.end(), [&](trio& cor){
		cor.r = rand()%256;
		cor.g = rand()%256;
		cor.b = rand()%256;
	});
}

void descolorir_cobra(vector<trio>& cores, trio cor_segmentos={0, 0, 0}){
            for_each(cores.begin(), cores.end(), [&](trio& cor){
                cor.r = cor_segmentos.r;
                cor.g = cor_segmentos.g;
                cor.b = cor_segmentos.b;
            });
        }


int main(int argc, char* argv[]) {
	Player p1{WIDTH, HEIGHT, {SDLK_UP, SDLK_DOWN, SDLK_RIGHT, SDLK_LEFT}};

	//Criar Janela
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Snake",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
							  WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	//Variaveis de controle e configuracao
	vector<SDL_Rect> macas(frequencia_maca);
	sortear_macas(macas, true);

	SDL_Event evento;
	int rodar=1;

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
				}
			}
		}
		//Mover cabeca
		p1.mover_cobra(p1.direcao);

		//Colisao macas
		for_each(macas.begin(), macas.end(), [&](auto& rect_maca){
			if(SDL_HasIntersection(&rect_maca, &p1.cabeca)){
				p1.num_segmentos+=10;
				total_macas--;
				rect_maca.x = -10;
				rect_maca.y = -10;
			}
		});

		if(frequencia_maca-total_macas >= minimo_sorteio){
			sortear_macas(macas);
			total_macas = frequencia_maca;
		}

		//Colisao minhoca
		p1.colisao_cobra(p1.segmentos_cobra);

		//Mover cobra
		p1.atualizar_posicoes();

		//Plano de Fundo
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderClear(renderer);

		//Desenhar macas
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 150);
		for(int i=0; i<frequencia_maca; i++){
			SDL_RenderFillRect(renderer, &(macas[i]));
		}

		//Desenhar a minhoca
		p1.desenhar_cobra(&renderer);

		SDL_RenderPresent(renderer);

		SDL_Delay(100);
	}

	return 0;
}

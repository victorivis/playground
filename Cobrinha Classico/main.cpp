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
	//Criar Janela
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Snake",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
							  WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	//Variaveis de controle e configuracao
	enum Direcoes{
		Pausa=-1, Cima, Direita, Baixo, Esquerda
	};
	
	SDL_Rect cabeca = {500, 500, TAM_COBRA, TAM_COBRA};
	deque<SDL_Rect> segmentos_cobra;
	vector<SDL_Rect> macas(frequencia_maca);
	vector<trio> cores;

	sortear_macas(macas, true);

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
					case SDLK_UP: if(direcao!=Baixo) direcao=Cima; break;
					case SDLK_DOWN: if(direcao!=Cima) direcao=Baixo; break;
					case SDLK_RIGHT: if(direcao!=Esquerda) direcao=Direita; break;
					case SDLK_LEFT:	if(direcao!=Direita) direcao=Esquerda; break;

					case '=': VEL++; break;
					case '-': VEL--; break;
					
					//Inverte controles
					case '0': VEL = -VEL; direcao= (direcao+2)%4; break;
					
					// Colorir/descolorir cobra
					case 'c': 
						cobra_colorida = !cobra_colorida; 
						cobra_colorida ? colorir_cobra(cores) : descolorir_cobra(cores);
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
		switch(direcao){
			case Cima: cabeca.y = (cabeca.y-VEL+HEIGHT)%HEIGHT; break;
			case Baixo: cabeca.y = (cabeca.y+VEL+HEIGHT)%HEIGHT; break;
			case Direita: cabeca.x = (cabeca.x+VEL+WIDTH)%WIDTH; break;
			case Esquerda: cabeca.x = (cabeca.x-VEL+WIDTH)%WIDTH; break;
		}

		//Colisao macas
		for_each(macas.begin(), macas.end(), [&](auto& rect_maca){
			if(SDL_HasIntersection(&rect_maca, &cabeca)){
				num_segmentos+=10;
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
		for_each(segmentos_cobra.begin(), segmentos_cobra.end(), [&](auto& segmento){
			if(SDL_HasIntersection(&segmento, &cabeca)){
				num_segmentos = 1;
				//cout << "Colisao cabeca\n";
			}
		});

		//Mover cobra
		segmentos_cobra.push_front(cabeca);

		while(segmentos_cobra.size() > num_segmentos){
			segmentos_cobra.pop_back();
		}

		while(cores.size() < segmentos_cobra.size()){
			if(cobra_colorida){
				cores.push_back({rand()%256, rand()%256, rand()%256});
			}
			else {
				cores.push_back({0, 0, 0});
			} 
		}

		while(cores.size() > segmentos_cobra.size()){
			cores.pop_back(); 
		}

		//Plano de Fundo
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderClear(renderer);

		//Desenhar a minhoca
		
		for(int i=0; i<segmentos_cobra.size(); i++){
			SDL_SetRenderDrawColor(renderer, cores[i].r, cores[i].g, cores[i].b, 255);
			SDL_RenderFillRect(renderer, &(segmentos_cobra[i]));
		};

		//Desenhar macas
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 150);
		for(int i=0; i<frequencia_maca; i++){
			SDL_RenderFillRect(renderer, &(macas[i]));
		}

		SDL_RenderPresent(renderer);

		SDL_Delay(100);
	}
	
	//Liberando memoria
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

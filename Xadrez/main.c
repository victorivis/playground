#include <SDL2/SDL.h>
#include "som.h"

const int WIDTH = 1080, HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void tabuleiro(int casas_por_linha, int inicio_x, int inicio_y, int razao){
	//int razao=HEIGHT/casas_por_linha;
	int padrao=1;

	for(int j=0; j<casas_por_linha; j++){
		for(int i=0; i<casas_por_linha; i++){
			if(padrao) SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			else SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

			SDL_Rect r = {i*razao+inicio_x, j*razao+inicio_y, razao, razao};
			SDL_RenderFillRect(renderer, &r);
			padrao = !padrao;
		}
		
		if(casas_por_linha%2==0) padrao = !padrao;
	}
}

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Xadrez",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
							  WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
	
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	int inicio_x=10;
	int inicio_y = 30;
	int num_casas = 8;
	int razao = 50;

	int final_x = inicio_x + (num_casas)*razao;
	int final_y = inicio_y + (num_casas)*razao;

	SDL_Event evento;
	int rodar=1;
	while(rodar){
		while(SDL_PollEvent(&evento)){
			if(evento.type == SDL_QUIT) rodar=0;

			else if(evento.type == SDL_KEYDOWN){
				switch(evento.key.keysym.sym){
					case SDLK_ESCAPE:
						rodar=0;
						break;				
				}
			}

			else if(evento.type == SDL_MOUSEBUTTONDOWN){
				int pos_x, pos_y;
				SDL_GetMouseState(&pos_x, &pos_y);

				int bool_x=0, bool_y=0;
				if(pos_x <= final_x && pos_x >= inicio_x) bool_x=1;
				if(pos_y <= final_y && pos_y >= inicio_y) bool_y=1;

				if(bool_x && bool_y) playSound(440);
			}
		}
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderClear(renderer);

		tabuleiro(num_casas, inicio_x, inicio_y, razao);
		SDL_RenderPresent(renderer);
		

		SDL_Delay(100);
	}

	return 0;
}



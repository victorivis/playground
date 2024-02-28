#include <SDL2/SDL.h>
//#include <bits/stdc++h>
#include <stdio.h>

//using namespace std;

const int WIDTH = 1080, HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void tabuleiro(int n, int inicio_x, int inicio_y, int razao){
	//int razao=HEIGHT/n;
	int padrao=1;

	for(int j=0; j<n; j++){
		for(int i=0; i<n; i++){
			if(padrao) SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			else SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

			SDL_Rect r = {i*razao+inicio_x, j*razao+inicio_y, razao, razao};
			SDL_RenderFillRect(renderer, &r);
			padrao = !padrao;
		}
		
		if(n%2==0) padrao = !padrao;
	}
	SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Xadrez",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
							  WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
	
	//SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
	
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	int inicio_x=10;
	int inicio_y = 30;
	int num_casas = 8;
	int razao = 50;

	int final_x = inicio_x + (num_casas-1)*razao;
	int final_y = inicio_y + (num_casas-1)*razao;

	//vector<vector<char>> lista;
	//tabuleiro(num_casas, inicio_x, inicio_y, razao, lista);

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

				if(bool_x && bool_y) printf("existe\a\n");
			}
		}

		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		tabuleiro(num_casas, inicio_x, inicio_y, razao);

		SDL_Delay(100);
	}

	return 0;
}



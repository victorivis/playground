#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

const int WIDTH = 1080, HEIGHT = 600;

int main(int argc, char* argv[]) {
	SDL_Rect r{100, 100, 250, 200};

	//Criando Janela
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Alface's Life",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
							  WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	//Inserindo a imagem na memoria RAM
	SDL_Surface* lettuce_sur = SDL_LoadBMP("assets/lettuce.bmp");
	SDL_Surface* carrot_sur = SDL_LoadBMP("assets/carrot.bmp");
	SDL_Surface* cadeirante_sur = SDL_LoadBMP("assets/wheelchair_lettuce.bmp");

	//Inserindo a imagem na memoria VRAM
	int contador=0;
	std::vector<SDL_Texture*> conjunto_imagens;
	conjunto_imagens.push_back(SDL_CreateTextureFromSurface(renderer, lettuce_sur));
	conjunto_imagens.push_back(SDL_CreateTextureFromSurface(renderer, carrot_sur));
	conjunto_imagens.push_back(SDL_CreateTextureFromSurface(renderer, cadeirante_sur));
	
	//Libera superficie
	SDL_FreeSurface(lettuce_sur);
	SDL_FreeSurface(carrot_sur);
	SDL_FreeSurface(cadeirante_sur);

	//Variaveis de Controle
	SDL_Event evento;
	int rodar=1;
	int VEL=10;
	
	//Executar jogo
	while(rodar){
		while(SDL_PollEvent(&evento)){
			if(evento.type == SDL_QUIT) rodar=0;

			else if(evento.type == SDL_KEYDOWN){
				int solve_x = (WIDTH-r.w);
				int solve_y = (HEIGHT-r.h);
				switch(evento.key.keysym.sym){
					case SDLK_ESCAPE:
						rodar=0;
						break;
					case SDLK_UP: r.y = (r.y-VEL+solve_y)%solve_y; break;	
					case SDLK_DOWN: r.y = (r.y+VEL+solve_y)%solve_y; break;	
					case SDLK_RIGHT: r.x = (r.x+VEL+solve_x)%solve_x; break;	
					case SDLK_LEFT: r.x = (r.x-VEL+solve_x)%solve_x; break;

					/*
					case SDLK_UP: r.y-=VEL; break;	
					case SDLK_DOWN: r.y+=VEL; break;	
					case SDLK_RIGHT: r.x+=VEL; break;	
					case SDLK_LEFT: r.x-=VEL; break;
					*/

					case 'w': r.h-=VEL; break;	
					case 's': r.h+=VEL; break;	
					case 'd': r.w+=VEL; break;	
					case 'a': r.w-=VEL; break;	
					case 'g': contador=(contador+1)%conjunto_imagens.size();
				}
			}
		}

		//Carregar plano de fundo
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderClear(renderer);

		//Carregar imagem
		SDL_RenderCopy(renderer, conjunto_imagens[contador], NULL, &r);
		SDL_RenderPresent(renderer);

		SDL_Delay(5);
	}
	int total = (int) conjunto_imagens.size()-1;
	for(int i=total; i>=0; i--){
		SDL_DestroyTexture(conjunto_imagens[i]);
		conjunto_imagens.pop_back();
	}

	return 0;
}


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

const int WIDTH = 1080, HEIGHT = 600;

int main(int argc, char* argv[]) {
	SDL_Rect r{100, 100, 500, 100};

	//Criando Janela
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Xadrez",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
							  WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	//Inserindo a imagem na memoria RAM
	SDL_Surface* lettuce_sur = IMG_Load("assets/lettuce.png");

	//Inserindo a imagem na memoria VRAM
	SDL_Texture* lettuce_tex = SDL_CreateTextureFromSurface(renderer, lettuce_sur);
	
	//Libera superficie
	SDL_FreeSurface(lettuce_sur);

	//Variaveis de Controle
	SDL_Event evento;
	int rodar=1;
	int VEL=3;
	
	//Executar jogo
	while(rodar){
		while(SDL_PollEvent(&evento)){
			if(evento.type == SDL_QUIT) rodar=0;

			else if(evento.type == SDL_KEYDOWN){
				switch(evento.key.keysym.sym){
					case SDLK_ESCAPE:
						rodar=0;
						break;
					case SDLK_UP: r.y-=VEL; break;	
					case SDLK_DOWN: r.y+=VEL; break;	
					case SDLK_RIGHT: r.x+=VEL; break;	
					case SDLK_LEFT: r.x-=VEL; break;

					case 'w': r.h-=VEL; break;	
					case 's': r.h+=VEL; break;	
					case 'd': r.w+=VEL; break;	
					case 'a': r.w-=VEL; break;	
				}
			}
		}

		//Carregar plano de fundo
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderClear(renderer);

		//Carregar imagem
		SDL_RenderCopy(renderer, lettuce_tex, NULL, &r);
		SDL_RenderPresent(renderer);

		SDL_Delay(5);
	}

	return 0;
}


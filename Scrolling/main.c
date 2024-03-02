#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

const int TEXTURE_H = 2000;
const int TEXTURE_W = 2000;
const int SCREEN_H = 1000;
const int SCREEN_W = 1000;
const int NUM_PONTOS = 10000;

int main(int argc, char* argv[]) {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, 0, &window, &renderer);
	
	SDL_Rect origem = {0, 0, SCREEN_W/8, SCREEN_H/8};
	SDL_Rect destino = {10, 10, SCREEN_W-20, SCREEN_H-20};

	SDL_Texture* textura = SDL_CreateTexture(renderer,
                            SDL_PIXELFORMAT_RGBA8888,
                            SDL_TEXTUREACCESS_TARGET,
                            TEXTURE_W,
                            TEXTURE_H);

	SDL_Point pv[NUM_PONTOS];

	for(int i=0; i<	NUM_PONTOS; i++){
		pv[i].x = rand()%TEXTURE_H;
		pv[i].y = rand()%TEXTURE_W;
	}

	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	SDL_Event evento;
	int rodar=1;
	int VEL=3;
	int entropia=3;
	while(rodar){
		while(SDL_PollEvent(&evento)){
			if(evento.type == SDL_QUIT) rodar=0;

			if(evento.type == SDL_KEYDOWN){
				switch(evento.key.keysym.sym){
					case SDLK_ESCAPE: rodar=0; break;
					case SDLK_UP: origem.y-=VEL; break;	
					case SDLK_DOWN: origem.y+=VEL; break;	
					case SDLK_RIGHT: origem.x+=VEL; break;	
					case SDLK_LEFT: origem.x-=VEL; break;
					case SDLK_1: origem.w *= 2; origem.h *= 2; break;
					case SDLK_2: origem.w /= 2; origem.h /= 2; break;
					case SDLK_3: VEL+=2; break;
					case SDLK_4: VEL-=2; break;
					case SDLK_5: entropia+=2; break;
					case SDLK_6: entropia-=2; break;
				}
			}
		}
		//Clear texture
		SDL_SetRenderTarget(renderer, textura);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);


		//Move position of dots around
		for(int i=0; i<NUM_PONTOS; i++){
			pv[i].x += rand()%entropia - entropia/2;
			pv[i].y += rand()%entropia - entropia/2;
		}

		//Draw dots to thescreen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawPoints(renderer, pv, NUM_PONTOS);

		//Copy selection from texture to the screen
		SDL_SetRenderTarget(renderer, NULL);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, textura, &origem, &destino);
		SDL_RenderPresent(renderer);

		SDL_Delay(50);
	}

	return 0;
}

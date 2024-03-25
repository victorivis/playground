#include <SDL2/SDL.h>
#include <stdio.h>

const int WIDTH = 1080, HEIGHT = 600;

int main(int argc, char* argv[]) {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
	
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
	
	SDL_Rect r = {10, 10, 40, 40};
	SDL_RenderFillRect(renderer, &r);
	SDL_RenderPresent(renderer);

	int rodar = 1;
	SDL_Event evento;
	int VEL=3;
	int ACEL=5;
	int dica=0;
	int trocar_tecla=1;
	int loop_reset=0;
	while(rodar){		
		while(SDL_PollEvent(&evento)){
			if(evento.type == SDL_QUIT && dica<12) printf("Nao vou fechar trouxa kkkkkk\n"), dica++;//rodar=0, printf("Saindo\n");	
			else if(evento.type == SDL_QUIT) printf("Calma, eh so apertar esc que fecha\n");
			
			
			if(evento.type == SDL_KEYDOWN){
				if(trocar_tecla){
					printf("%d ", evento.key.keysym.sym);
					if(evento.key.keysym.sym>=97 && evento.key.keysym.sym<=122) printf("%c", evento.key.keysym.sym), trocar_tecla=0;
					printf("\n");
				}

				switch(evento.key.keysym.sym){
					case SDLK_UP:
						if(trocar_tecla) printf("Cima\n"), trocar_tecla=0;
						r.y-=VEL;
						break;
					case SDLK_DOWN:
						if(trocar_tecla) printf("Baixo\n"), trocar_tecla=0;
						r.y+=VEL;
						break;
					case SDLK_RIGHT:
						if(trocar_tecla) printf("Direita\n"), trocar_tecla=0;
						r.x+=VEL;
						break;
					case SDLK_LEFT:
						if(trocar_tecla) printf("Esquerda\n"), trocar_tecla=0;
						r.x-=VEL;
						break;
					case SDLK_ESCAPE:
						printf("Esq\n");
						rodar=0;
						break;

					case '=':
						printf("velocidade: %d\n", VEL);
						VEL+=ACEL;
						break;

					case '-':
						printf("velocidade: %d\n", VEL);
						VEL-=ACEL;
						break;
					
					case 'r':
						SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
						SDL_RenderClear(renderer);

						SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
						SDL_RenderPresent(renderer);
						break;
						
					case 'l':
						loop_reset = !loop_reset;
						break;
				}
			}
			
			if(evento.type == SDL_KEYUP){
				//printf("Tecla solta\n");
				trocar_tecla=1;
			}

			if(evento.type == SDL_MOUSEBUTTONDOWN){
				printf("Pintando\n");
				while(evento.type != SDL_MOUSEBUTTONUP){
					SDL_PollEvent(&evento);
					SDL_GetMouseState(&r.x, &r.y);
					
					SDL_RenderFillRect(renderer, &r);
					SDL_RenderPresent(renderer);
				}
			}
		}
		
		if(loop_reset){
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
			SDL_RenderPresent(renderer);
		}
		
		SDL_RenderFillRect(renderer, &r);
		SDL_RenderPresent(renderer);
		
		if(loop_reset) SDL_Delay(50);
	}
	
	//Liberando memoria e subsistemas
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

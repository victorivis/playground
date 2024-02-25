#include <SDL2/SDL.h>
#include <stdio.h>

const int WIDTH = 1000;
const int HEIGHT = 600;
const int TAM_COBRA = 10;
int VEL = 5;
int num_segmentos = 16;
int novo_movimento=1;

enum direcoes{CIMA, BAIXO, ESQUERDA, DIREITA};

int abs(int n){
	if(n<0) n=-n;
	return n;
}

void mover_cobra(SDL_Rect cobra[num_segmentos], int direcao){
	if(novo_movimento)
	for(int i=num_segmentos-1; i>0; i--){
		int mov_x = cobra[i].x-cobra[i-1].x;
		int mov_y = cobra[i].y-cobra[i-1].y;

		if(mov_x){
			if(mov_x>0){
				cobra[i].x = (cobra[i].x+VEL)%WIDTH;
			}
			else{
				cobra[i].x = (cobra[i].x-VEL+WIDTH)%WIDTH;
			}
		}
		else{
			if(mov_y>0){
				cobra[i].y = (cobra[i].y+VEL)%HEIGHT;
			}
			else{
				cobra[i].y = (cobra[i].y-VEL+HEIGHT)%HEIGHT;
			}
		}
	}
	else
		for(int i=num_segmentos-1; i>0; i--){
			cobra[i].x = cobra[i-1].x;
			cobra[i].y = cobra[i-1].y;
		}
	
	switch(direcao){
		case 0: cobra[0].y = (cobra[0].y-VEL+HEIGHT)%HEIGHT; break;	
		case 1: cobra[0].y = (cobra[0].y+VEL)%HEIGHT; break;	
		case 2: cobra[0].x = (cobra[0].x+VEL)%WIDTH; break;	
		case 3: cobra[0].x = (cobra[0].x-VEL+WIDTH)%WIDTH; break;
	}
}

int main(int argc, char* argv[]) {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);

	SDL_Rect segmentos_cobra[num_segmentos];

	for(int i=0; i<num_segmentos; i++){
		segmentos_cobra[i].x = 100+TAM_COBRA*i;
		segmentos_cobra[i].y = 100;
		segmentos_cobra[i].w = TAM_COBRA;
		segmentos_cobra[i].h = TAM_COBRA;
	}
	//segmentos_cobra.push_back({100, 100, TAM_COBRA, TAM_COBRA});

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	
	int rodar = 1;
	SDL_Event evento;
	int ultima_direcao=-1;
	while(rodar){
		while(SDL_PollEvent(&evento)){
			if(evento.type == SDL_QUIT) rodar=0;

			if(evento.type == SDL_KEYDOWN){
				switch(evento.key.keysym.sym){
					case SDLK_ESCAPE: rodar=0; break;
					case SDLK_UP: /*if(ultima_direcao!=0 && ultima_direcao!=1)*/ mover_cobra(segmentos_cobra, 0), ultima_direcao=0; break;	
					case SDLK_DOWN: /*if(ultima_direcao!=0 && ultima_direcao!=1)*/ mover_cobra(segmentos_cobra, 1), ultima_direcao=1; break;	
					case SDLK_RIGHT: /*if(ultima_direcao!=2 && ultima_direcao!=3)*/ mover_cobra(segmentos_cobra, 2), ultima_direcao=2; break;	
					case SDLK_LEFT: /*if(ultima_direcao!=2 && ultima_direcao!=3)*/ mover_cobra(segmentos_cobra, 3), ultima_direcao=3; break;
					
					case SDLK_3: VEL+=2; break;
					case SDLK_4: VEL-=2; break;
					case SDLK_7: novo_movimento = !novo_movimento;
					/*
					case SDLK_1: origem.w *= 2; origem.h *= 2; break;
					case SDLK_2: origem.w /= 2; origem.h /= 2; break;
					case SDLK_5: entropia+=2; break;
					case SDLK_6: entropia-=2; break;
					*/
				}
			}
		}

		if(ultima_direcao!=-1){
			mover_cobra(segmentos_cobra, ultima_direcao);
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		for(int i=0; i<num_segmentos; i++){
			SDL_RenderFillRect(renderer, &segmentos_cobra[i]);
			//SDL_RenderDrawPoint(renderer, segmentos_cobra[i].x, segmentos_cobra[i].y);
		}

		SDL_RenderPresent(renderer);
		//std::cout << segmentos_cobra[0].x << " " << segmentos_cobra[0].y << "\n";
		printf("%d %d\n", segmentos_cobra[0].x, segmentos_cobra[0].y);

		SDL_Delay(100);
	}

	return 0;
}

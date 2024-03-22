#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

const int WIDTH = 1000;
const int HEIGHT = 600;
const int TAM_COBRA = 10;
int VEL = TAM_COBRA;//5;
int num_segmentos = 16;
int novo_movimento=0;
int restricao_movimento=1;
int cobra_pisca=0;
int modo_de_piscar=1;
int frequencia = 5;

enum direcoes{CIMA, BAIXO, ESQUERDA, DIREITA};

typedef struct{
	char r;
	char g;
	char b;
} Trio;

void adicionar_segmento(SDL_Rect** cobra, int num, Trio** cores){
	if(num_segmentos+num > 0){
		*cobra = realloc(*cobra, sizeof(SDL_Rect) * (num_segmentos+num));
		*cores = realloc(*cores, sizeof(Trio) * (num_segmentos+num));
		for(int i=num_segmentos; i<num_segmentos+num; i++){
			(*cobra)[i].x = 0;
			(*cobra)[i].y = 0;
			(*cobra)[i].h = TAM_COBRA;
			(*cobra)[i].w = TAM_COBRA;
			
			Trio t = {rand()%256, rand()%256, rand()%256};
			(*cores)[i] = t;
		}
		num_segmentos+=num;
	}
}

void mover_cobra(SDL_Rect* cobra, int direcao){
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

void andar_cores(Trio** cores){
	for(int i=1; i<num_segmentos; i++){
		(*cores)[i-1] = (*cores)[i];
	}
	Trio t = {rand()%256, rand()%256, rand()%256};
	(*cores)[num_segmentos-1] = t;
}

void trocar_cores(Trio** cores){
	for(int i=0; i<num_segmentos; i++){
		Trio t = {rand()%256, rand()%256, rand()%256};
		(*cores)[i] = t;
	}
}

void cor_preta(Trio** cores){
	for(int i=0; i<num_segmentos; i++){
		Trio t = {0, 0, 0};
		(*cores)[i] = t;
	}
}

int main(int argc, char* argv[]) {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);

	SDL_Rect* segmentos_cobra = malloc(sizeof(SDL_Rect) * num_segmentos);
	Trio* cores = malloc(sizeof(Trio) * num_segmentos);

	for(int i=0; i<num_segmentos; i++){
		segmentos_cobra[i].x = 100+TAM_COBRA*i;
		segmentos_cobra[i].y = 100;
		segmentos_cobra[i].w = TAM_COBRA;
		segmentos_cobra[i].h = TAM_COBRA;

		Trio t = {rand()%256, rand()%256, rand()%256};
		cores[i] = t;
	}
	//segmentos_cobra.push_back({100, 100, TAM_COBRA, TAM_COBRA});

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	
	int rodar = 1;
	SDL_Event evento;
	int ultima_direcao=-1;
	int contador=0;
	while(rodar){
		while(SDL_PollEvent(&evento)){
			if(evento.type == SDL_QUIT) rodar=0;

			if(evento.type == SDL_KEYDOWN){
				switch(evento.key.keysym.sym){
					case SDLK_ESCAPE: rodar=0; break;
					case SDLK_UP: if(!restricao_movimento || (ultima_direcao!=0 && ultima_direcao!=1)) mover_cobra(segmentos_cobra, 0), ultima_direcao=0; break;	
					case SDLK_DOWN: if(!restricao_movimento || (ultima_direcao!=0 && ultima_direcao!=1)) mover_cobra(segmentos_cobra, 1), ultima_direcao=1; break;	
					case SDLK_RIGHT: if(!restricao_movimento || (ultima_direcao!=2 && ultima_direcao!=3)) mover_cobra(segmentos_cobra, 2), ultima_direcao=2; break;	
					case SDLK_LEFT: if(!restricao_movimento || (ultima_direcao!=2 && ultima_direcao!=3)) mover_cobra(segmentos_cobra, 3), ultima_direcao=3; break;
					
					case SDLK_1: restricao_movimento = !restricao_movimento; break;
					case SDLK_2: VEL+=2; printf("velocidade: %d\n", VEL); break;
					case SDLK_3: VEL-=2; printf("velocidade: %d\n", VEL); break;
					case SDLK_4: cor_preta(&cores); break;
					case SDLK_5: trocar_cores(&cores); break;
					case SDLK_6: cobra_pisca = !cobra_pisca; break;
					case SDLK_7: novo_movimento = !novo_movimento; break;
					case SDLK_8: adicionar_segmento(&segmentos_cobra, 3, &cores); break;
					case SDLK_9: adicionar_segmento(&segmentos_cobra, -3, &cores); break;
					case 'p': ultima_direcao=-1; break;
					case 'c': modo_de_piscar = !modo_de_piscar; break;
					case 'v': frequencia++; break;
					case 'b': if(frequencia>1) frequencia--; break;
				}
			}
		}

		if(ultima_direcao!=-1){
			mover_cobra(segmentos_cobra, ultima_direcao);
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		if(cobra_pisca){
			if(contador==0){
				if(modo_de_piscar) trocar_cores(&cores);
				else andar_cores(&cores);
			}
			contador=(contador+1)%frequencia;
		}

		for(int i=0; i<num_segmentos; i++){
			SDL_SetRenderDrawColor(renderer, cores[i].r, cores[i].g, cores[i].b, 255);
			//SDL_SetRenderDrawColor(renderer, rand()%256, rand()%256, rand()%256, 255);
			SDL_RenderFillRect(renderer, &segmentos_cobra[i]);
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

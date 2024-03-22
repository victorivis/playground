#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>

const int WIDTH = 1080, HEIGHT = 600;

int main(int argc, char* argv[]) {
	SDL_Rect r{100, 100, 250, 200};

	//Criando Janela
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Awesome Texting :o",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
							  WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	//Variaveis de Controle
	SDL_Event evento;
	int rodar=1;
	int VEL=10;

	//Iniciando funcoes de texto
	TTF_Init();

	//Definindo tamanho da fonte
	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 60);
	SDL_Color Preto = {0, 0, 0, 255};
	SDL_Color Vermelho = {230, 0, 0, 255};

	SDL_Surface* surfaceMessage = 
		TTF_RenderText_Solid(Sans, "Ora, ora se nao eh mais memoria prestes a ser estourada", Preto); 

	SDL_Surface* sur_ajustavel =
		TTF_RenderText_Solid(Sans, "Um pouco melhor agora", Vermelho); 

	// now you can convert it into a texture
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	
	SDL_Texture* tex_ajustavel = SDL_CreateTextureFromSurface(renderer, sur_ajustavel);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 100;  //controls the rect's x coordinate 
	Message_rect.y = 100; // controls the rect's y coordinte
	Message_rect.w = 500; // controls the width of the rect
	Message_rect.h = 50; // controls the height of the rect


	int texX = 0;
	int texY = 150;
	int texW;
	int texH;
	SDL_QueryTexture(tex_ajustavel, NULL, NULL, &texW, &texH);
	SDL_Rect tamanho_ajustado = { texX, texY, texW, texH };
	
	//Executar jogo
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
		}

		//Carregar plano de fundo
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
		SDL_RenderCopy(renderer, tex_ajustavel, NULL, &tamanho_ajustado);

		SDL_RenderPresent(renderer);

		SDL_Delay(120);
	}
	TTF_CloseFont(Sans);
	TTF_Quit();

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);

	SDL_FreeSurface(sur_ajustavel);
	SDL_DestroyTexture(tex_ajustavel);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}


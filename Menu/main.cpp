#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>

enum Operacao{
    Continuar, Sair
};

int rodar_menu(SDL_Renderer*& renderer){
    //Inicializando bibliotecas SDL_ttf
    TTF_Init();

    //Criando variaveis do menu
    int retorno;
    TTF_Font* fonte = TTF_OpenFont("Sans.ttf", 64);
    const int NUMMENU=2;
    const char rotulo[NUMMENU][15] = {"Continuar", "Sair"};

    SDL_Surface* molde[NUMMENU];
    SDL_Texture* textura[NUMMENU];
    bool selecionado[NUMMENU] = {false, false};
    
    //Cores preto e vermelho
    SDL_Color cor[2] = {{255, 255, 255, 255}, {255, 0, 0, 255}};

    for(int i=0; i<NUMMENU; i++){
        molde[i] = TTF_RenderText_Solid(fonte, rotulo[i], cor[0]);
        textura[i] = SDL_CreateTextureFromSurface(renderer, molde[i]);
    }

    SDL_Rect pos_inicial={0, 0, 100, 100};
    SDL_Rect posicao[NUMMENU];
    for(int i=0; i<NUMMENU; i++){
        posicao[i]=pos_inicial;
        pos_inicial.y += pos_inicial.h;
    }

    //Main loop
    bool rodar_menu=true;
    SDL_Event evento_menu;
    while(rodar_menu){
        while(SDL_PollEvent(&evento_menu)){
            if(evento_menu.type == SDL_QUIT){
                retorno=Sair;
                rodar_menu=false;
            }

            else if(evento_menu.type == SDL_KEYDOWN){
				switch(evento_menu.key.keysym.sym){
					case SDLK_ESCAPE:
                        retorno=Continuar;
                        rodar_menu=false;
                        break;
				}
			}

            else if(evento_menu.type == SDL_MOUSEMOTION){
                int mouse_x;
                int mouse_y;
                SDL_GetMouseState(&mouse_x, &mouse_y);

                for(int i=0; i<NUMMENU; i++){
                    bool eixo_x = (posicao[i].x <= mouse_x && posicao[i].x+posicao[i].w >= mouse_x);
                    bool eixo_y = (posicao[i].y <= mouse_y && posicao[i].y+posicao[i].h >= mouse_y);

                    if(eixo_x && eixo_y){
                        if(selecionado[i]==false){
                            selecionado[i]=true;
                            SDL_DestroyTexture(textura[i]);
                            SDL_FreeSurface(molde[i]);

                            molde[i] = TTF_RenderText_Solid(fonte, rotulo[i], cor[1]);
                            textura[i] = SDL_CreateTextureFromSurface(renderer, molde[i]);
                        }
                    }
                    else{
                        if(selecionado[i]==true){
                            selecionado[i]=false;
                            SDL_DestroyTexture(textura[i]);
                            SDL_FreeSurface(molde[i]);

                            molde[i] = TTF_RenderText_Solid(fonte, rotulo[i], cor[0]);
                            textura[i] = SDL_CreateTextureFromSurface(renderer, molde[i]);
                        }
                    }
                }
            }

            else if(evento_menu.type == SDL_MOUSEBUTTONDOWN){
                for(int i=0; i<NUMMENU; i++){
                    if(selecionado[i]){
                        retorno = i;
                        rodar_menu=false;
                        break;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderClear(renderer);

        for(int i=0; i<NUMMENU; i++){
            SDL_RenderCopy(renderer, textura[i], NULL, &posicao[i]);
        }

		SDL_RenderPresent(renderer);
        SDL_Delay(120);
    }

    //Liberando os ponteiros
    TTF_CloseFont(fonte);
    for(int i=0; i<NUMMENU; i++){
        SDL_FreeSurface(molde[i]);
	    SDL_DestroyTexture(textura[i]);   
    }
    //Liberando os subsistemas de SDL_ttf
    TTF_Quit();
    
    return retorno;
}	

const int WIDTH = 1080, HEIGHT = 600;

int main(int argc, char* argv[]) {
    //Inicializando subsistemas
    SDL_Init(SDL_INIT_VIDEO);

    //Criando Janela
    SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	window = SDL_CreateWindow("Um simples menu (aperte esc)",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
							  WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	//Variaveis de Controle
	SDL_Event evento;
	int rodar=1;
	
	//Executar jogo
	while(rodar){
		while(SDL_PollEvent(&evento)){
			if(evento.type == SDL_QUIT) rodar=0;

			else if(evento.type == SDL_KEYDOWN){
				switch(evento.key.keysym.sym){
					case SDLK_ESCAPE:
                        int retorno = rodar_menu(renderer);

                        if(retorno==Sair){
                            rodar=0;
                        }
						break;
				}
			}
		}

		//Carregar plano de fundo
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);

		SDL_Delay(120);
	}

    //Liberando memoria
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}
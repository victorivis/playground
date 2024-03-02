#include <SDL2/SDL.h>
#include <iostream>
#include <cstdio>
#include "som.h"

const int WIDTH = 1080, HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

struct Lance{
	int src_i;
	int src_j;
	int dst_i;
	int dst_j;
};

enum Cor{
	Black, White
};

enum Pecas{
	Vazio, Agua, Borda,
	BlackPawn, BlackKnight, BlackBishop, BlackRook, BlackQueen, BlackKing,
	WhitePawn, WhiteKnight, WhiteBishop, WhiteRook, WhiteQueen, WhiteKing
};

enum Direcao{
    Norte, Sul, Leste, Oeste, Nordeste, Suldeste, Suldoeste, Noroeste
};

void executar_lance(std::vector<std::vector<int>>& tabuleiro, Lance& lance){
    tabuleiro[lance.dst_i][lance.dst_j] = tabuleiro[lance.src_i][lance.src_j];
    tabuleiro[lance.src_i][lance.src_j] = Vazio;
}

bool mover_peca(std::vector<std::vector<int>>& tabuleiro, std::pair<int, int>& origem, int direcao, bool capturar){
    int tamanho = tabuleiro.size();
    bool saida;
    switch(direcao){
        case Norte:
            origem.first+1 < tamanho && (capturar || tabuleiro[origem.first+1][origem.second]==Vazio) ? 
                saida=true : saida=false; break;
        
        case Sul:
            origem.first-1 >= 0 && (capturar || tabuleiro[origem.first-1][origem.second]==Vazio) ? 
                saida=true : saida=false; break;
                
        case Leste:
            origem.second+1 < tamanho && (capturar || tabuleiro[origem.first][origem.second+1]==Vazio) ? 
                saida=true : saida=false; break;
        
        case Oeste:
            origem.second-1 >= 0 && (capturar || tabuleiro[origem.first][origem.second-1]==Vazio) ? 
                saida=true : saida=false; break;
    }
    
    return saida;
}

std::vector<Lance> possiveis_lances(std::vector<std::vector<int>>& tabuleiro, int cor){
	std::vector<Lance> saida;
	
	for(uint8_t i=0; i<tabuleiro.size(); i++){
		for(uint8_t j=0; j<tabuleiro[i].size(); j++){
			switch(tabuleiro[i][j]){
				case WhitePawn: 
					if(j+1 <= tabuleiro[i].size()-1 && tabuleiro[i][j+1]==Vazio) 
					    saida.push_back({i, j, i, j+1}); 
					if(j+1 <= tabuleiro[i].size()-1 && tabuleiro[i][j+1]==Vazio) 
					    saida.push_back({i, j, i, j+1});
					if(j+1 <= tabuleiro[i].size()-1 && tabuleiro[i][j+1]==Vazio) 
					    saida.push_back({i, j, i, j+1}); 
					break;
/*
                case WhitePawn:
					if(mover_peca(Norte, false, tabuleiro, {i, j}))
						saida.push_back({i, j, i+1, j});

					break;
				
				case WhiteRook:
					int pos_x = i, pos_y = j;
					while(mover_peca(Norte, false, tabuleiro, {pos_x, pos_y})){
						saida.push_back({pos_y, pos_x, pos_y+1, pos_x});
					}	
*/
			}
		}
	}
	
	return saida;
}

void desenhar_tabuleiro(int casas_por_linha, int inicio_x, int inicio_y, int tam_quadrado){
	int padrao=1;

	for(int j=0; j<casas_por_linha; j++){
		for(int i=0; i<casas_por_linha; i++){
			if(padrao) SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			else SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

			SDL_Rect r = {i*tam_quadrado+inicio_x, j*tam_quadrado+inicio_y, tam_quadrado, tam_quadrado};
			SDL_RenderFillRect(renderer, &r);
			padrao = !padrao;
		}
		
		if(casas_por_linha%2==0) padrao = !padrao;
	}
}

int main(int argc, char* argv[]) {

	//Criar Janela
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Xadrez",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
							  WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
	
	//iniciar biblioteca som.h
	initMixer();
	int sound = loadSound("assets/move-self.mp3");
	setVolume(30);

	//Variaveis de configuracao
	int inicio_x=10;
	int inicio_y = 30;
	int casas_por_linha = 8;
	int tam_quadrado = 50;

	int final_x = inicio_x + (casas_por_linha)*tam_quadrado;
	int final_y = inicio_y + (casas_por_linha)*tam_quadrado;

	SDL_Event evento;
	int rodar=1;

	//Execucao do jogo
	while(rodar){
		while(SDL_PollEvent(&evento)){
			if(evento.type == SDL_QUIT) rodar=0;

			else if(evento.type == SDL_KEYDOWN){
				switch(evento.key.keysym.sym){
					case SDLK_ESCAPE:
						rodar=0;
						break;
					case 'q': playSound(sound);	break;
				}
			}

			//Verificar se foi clicado no tabuleiro
			else if(evento.type == SDL_MOUSEBUTTONDOWN){
				int pos_x, pos_y;
				SDL_GetMouseState(&pos_x, &pos_y);

				int bool_x=0, bool_y=0;
				if(pos_x <= final_x && pos_x >= inicio_x) bool_x=1;
				if(pos_y <= final_y && pos_y >= inicio_y) bool_y=1;

				if(bool_x && bool_y){
					printf("pos x: %d   pos y: %d\n", (pos_x-inicio_x)/tam_quadrado, (pos_y-inicio_y)/tam_quadrado);
					
					playSound(sound);
				}
			}
		}
		//Carregar plano de fundo
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderClear(renderer);

		desenhar_tabuleiro(casas_por_linha, inicio_x, inicio_y, tam_quadrado);
		SDL_RenderPresent(renderer);

		SDL_Delay(100);
	}

	//liberar memoria de som.h
	quitMixer();

	return 0;
}



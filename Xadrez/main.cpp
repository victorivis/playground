#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cstdio>
#include "som.h"

#define branco(peca) (peca>=WhitePawn && peca<=WhiteKing)
#define preto(peca) (peca>=BlackPawn && peca<=BlackKing)

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
    Norte, Sul, Leste, Oeste, Nordeste, Sudeste, Sudoeste, Noroeste, Linha, Casa, Pulo, Capturar, Mover, MoverCapturar
};

void executar_lance(std::vector<std::vector<int>>& tabuleiro, Lance& lance){
	//Previne de acessar memoria indevida
	if(lance.src_i<0 || lance.src_i>=tabuleiro.size()) printf("%d %d %d %d\n", lance.src_i, lance.src_j, lance.dst_i, lance.dst_j), exit(404);
	if(lance.src_j<0 || lance.src_j>=tabuleiro.size()) printf("%d %d %d %d\n", lance.src_i, lance.src_j, lance.dst_i, lance.dst_j), exit(404);
	if(lance.dst_i<0 || lance.dst_i>=tabuleiro.size()) printf("%d %d %d %d\n", lance.src_i, lance.src_j, lance.dst_i, lance.dst_j), exit(404);
	if(lance.dst_j<0 || lance.dst_j>=tabuleiro.size()) printf("%d %d %d %d\n", lance.src_i, lance.src_j, lance.dst_i, lance.dst_j), exit(404);
	
	tabuleiro[lance.dst_i][lance.dst_j] = tabuleiro[lance.src_i][lance.src_j];
    tabuleiro[lance.src_i][lance.src_j] = Vazio;
}

int calcular_destino(int direcao, std::pair<int, int>& origem, std::vector<std::vector<int>>& tabuleiro, int num_movimentos=1){
	switch(direcao){
		case Norte:
			return tabuleiro[origem.first-num_movimentos][origem.second];

		case Sul:
			return tabuleiro[origem.first+num_movimentos][origem.second];

		case Leste:
			return tabuleiro[origem.first][origem.second+num_movimentos];

		case Oeste:
			return tabuleiro[origem.first][origem.second-num_movimentos];

		case Nordeste:
			return tabuleiro[origem.first-num_movimentos][origem.second+num_movimentos];

		case Noroeste:
			return tabuleiro[origem.first-num_movimentos][origem.second-num_movimentos];

		case Sudeste:
			return tabuleiro[origem.first+num_movimentos][origem.second+num_movimentos];

		case Sudoeste:
			return tabuleiro[origem.first+num_movimentos][origem.second-num_movimentos];
	}	

	return -1;
}

//Refatorar esse codigo
bool movimento_permitido(int direcao, int tipo_lance, std::vector<std::vector<int>>& tabuleiro, std::pair<int, int> origem, int num_movimentos=1){
    int tamanho = tabuleiro.size();
    bool saida;
	
	int peca = tabuleiro[origem.first][origem.second];

	bool eh_branca;
	if(branco(peca)) eh_branca=true;
	else if(preto(peca)) eh_branca=false;
	else return false;

	int capturar=tipo_lance;
	if(tipo_lance == Capturar || tipo_lance == MoverCapturar){
		capturar=Capturar;
	}

    switch(direcao){
        case Sul:
            (origem.first+num_movimentos < tamanho && (capturar==Capturar || tabuleiro[origem.first+num_movimentos][origem.second]==Vazio)) ? 
                saida=true : saida=false; break;
        
        case Norte:
            (origem.first-num_movimentos >= 0 && (capturar==Capturar || tabuleiro[origem.first-num_movimentos][origem.second]==Vazio)) ? 
                saida=true : saida=false; break;
                
        case Leste:
            origem.second+num_movimentos < tamanho && (capturar==Capturar || tabuleiro[origem.first][origem.second+num_movimentos]==Vazio) ? 
                saida=true : saida=false; break;
        
        case Oeste:
            origem.second-num_movimentos >= 0 && (capturar==Capturar || tabuleiro[origem.first][origem.second-num_movimentos]==Vazio) ? 
                saida=true : saida=false; break;

		case Nordeste:
			(origem.first-num_movimentos >= 0 && origem.second+num_movimentos < tamanho) && (capturar==Capturar || tabuleiro[origem.first-num_movimentos][origem.second+num_movimentos]==Vazio) ? 
                saida=true : saida=false; break;

		case Noroeste:
			(origem.first-num_movimentos >= 0 && origem.second-num_movimentos >= 0) && (capturar==Capturar || tabuleiro[origem.first-num_movimentos][origem.second-num_movimentos]==Vazio) ? 
                saida=true : saida=false; break;

		case Sudeste:
			(origem.first+num_movimentos < tamanho && origem.second+num_movimentos < tamanho) && (capturar==Capturar || tabuleiro[origem.first+num_movimentos][origem.second+num_movimentos]==Vazio) ? 
                saida=true : saida=false; break;

		case Sudoeste:
			(origem.first+num_movimentos < tamanho && origem.second-num_movimentos >= 0) && (capturar==Capturar || tabuleiro[origem.first+num_movimentos][origem.second-num_movimentos]==Vazio) ? 
                saida=true : saida=false; break;
    }

    if(capturar==Capturar && saida){
		printf("If captura");
		int destino = calcular_destino(direcao, origem, tabuleiro);
		if(tipo_lance==MoverCapturar){
			if(eh_branca){
				return destino==Vazio || preto(destino);
			}
			else{
				return destino==Vazio || branco(destino);
			}
		}
		else if(tipo_lance==Capturar){
			if(eh_branca){
				return destino!=Vazio && preto(destino);
			}
			else{
				return destino!=Vazio && branco(destino);
			}
		}
		else{
			printf("Lance nao previsto");
			exit(1);
		}
	}
	else{
		printf("If mover");
		return saida;
	}
}

std::pair<int, int> par_mover_direcao(int direcao, std::pair<int, int>& origem, int num_movimentos=1){
	switch(direcao){
		case Sul:
			return {origem.first+num_movimentos, origem.second};
        
		case Norte:
			return {origem.first-num_movimentos, origem.second};
        
		case Leste:
			return {origem.first, origem.second+num_movimentos};

        case Oeste:
			return {origem.first, origem.second-num_movimentos};

		case Nordeste:
			return {origem.first-num_movimentos, origem.second+num_movimentos};

		case Noroeste:
			return {origem.first-num_movimentos, origem.second-num_movimentos};

		case Sudeste:
			return {origem.first+num_movimentos, origem.second+num_movimentos};

		case Sudoeste:
			return {origem.first+num_movimentos, origem.second-num_movimentos};
	}

	//Isso provavelmente quebra o codigo
	exit(1);
	return {-1, -1};
}

Lance mover_direcao(int direcao, std::pair<int, int> origem, int num_movimentos=1){
	switch(direcao){
		case Sul:
			return {origem.first, origem.second, origem.first+num_movimentos, origem.second};
        
		case Norte:
			return {origem.first, origem.second, origem.first-num_movimentos, origem.second};
        
		case Leste:
			return {origem.first, origem.second, origem.first, origem.second+num_movimentos};

        case Oeste:
			return {origem.first, origem.second, origem.first, origem.second-num_movimentos};

		case Nordeste:
			return {origem.first, origem.second, origem.first-num_movimentos, origem.second+num_movimentos};

		case Noroeste:
			return {origem.first, origem.second, origem.first-num_movimentos, origem.second-num_movimentos};

		case Sudeste:
			return {origem.first, origem.second, origem.first+num_movimentos, origem.second+num_movimentos};

		case Sudoeste:
			return {origem.first, origem.second, origem.first+num_movimentos, origem.second-num_movimentos};
	}

	//Isso provavelmente quebra o codigo
	exit(1);
	return {-1, -1, -1, -1};
}

void sequencia_lances(std::vector<int>& direcoes, std::pair<int, int> origem, int tipo_lance, std::vector<Lance>& lances, std::vector<std::vector<int>>& tabuleiro, int num_movimentos){
	for(int i=0; i<direcoes.size(); i++){
		if(tipo_lance == Linha){
			int contador=1;
			while(movimento_permitido(direcoes[i], Mover, tabuleiro, origem, contador)){
				printf("Origem: {%d %d}, contador: %d\n", origem.first, origem.second, contador);
				lances.push_back(mover_direcao(direcoes[i], origem, contador));
				contador+=num_movimentos;
			}
			if(movimento_permitido(direcoes[i], Capturar, tabuleiro, origem, contador)){
				lances.push_back(mover_direcao(direcoes[i], origem, contador));
			}
		}
		else{
			if(movimento_permitido(direcoes[i], tipo_lance, tabuleiro, origem, num_movimentos)){
				lances.push_back(mover_direcao(direcoes[i], origem, num_movimentos));
			}
		}
	}
}

std::vector<Lance> todos_possiveis_lances(std::vector<std::vector<int>>& tabuleiro){
	std::vector<Lance> saida;
	
	for(uint8_t i=0; i<tabuleiro.size(); i++){
		for(uint8_t j=0; j<tabuleiro[i].size(); j++){
			std::pair<int, int> origem = {i, j};
			std::vector<int> direcoes;
			switch(tabuleiro[i][j]){
				/*
                case BlackPawn:
					if(movimento_permitido(Sul, Mover, tabuleiro, {i, j}))
						saida.push_back(mover_direcao(Norte, {i, j}));

					direcoes = {Sudeste, Sudoeste};
					sequencia_lances(direcoes, origem, Capturar, saida, tabuleiro, 1);
					break;
				
				case WhitePawn:
					if(movimento_permitido(Norte, Mover, tabuleiro, {i, j}))
						saida.push_back(mover_direcao(Norte, {i, j}));

					direcoes = {Nordeste, Noroeste};
					sequencia_lances(direcoes, origem, Capturar, saida, tabuleiro, 1);
					break;
				*/

				case BlackKing:
				case WhiteKing:
					direcoes = {Norte, Sul, Leste, Oeste, Nordeste, Noroeste, Sudeste, Sudoeste};
					sequencia_lances(direcoes, origem, MoverCapturar, saida, tabuleiro, 1);
					break;

				case BlackRook:
				case WhiteRook:
					direcoes = {Norte, Sul, Leste, Oeste};
					sequencia_lances(direcoes, origem, Linha, saida, tabuleiro, 1);
					break;
				
				case BlackBishop:
				case WhiteBishop:
					direcoes = {Nordeste, Noroeste, Sudeste, Sudoeste};
					sequencia_lances(direcoes, origem, Linha, saida, tabuleiro, 1);
					break;

				case BlackQueen:
				case WhiteQueen:
					direcoes =  {Norte, Sul, Leste, Oeste, Nordeste, Noroeste, Sudeste, Sudoeste};
					sequencia_lances(direcoes, origem, Linha, saida, tabuleiro, 1);
					break;
			}
		}
	}
	
	return saida;
}

std::vector<std::vector<SDL_Rect>> criar_tabuleiro(int casas_por_linha, int inicio_x, int inicio_y, int tam_quadrado){
	
	std::vector<std::vector<SDL_Rect>> tabuleiro(casas_por_linha);
	for(int j=0; j<casas_por_linha; j++){
		for(int i=0; i<casas_por_linha; i++){
			tabuleiro[j].push_back({i*tam_quadrado+inicio_x, j*tam_quadrado+inicio_y, tam_quadrado, tam_quadrado});
		}
	}

	return tabuleiro;
}

void desenhar_tabuleiro(std::vector<std::vector<SDL_Rect>>& tabuleiro){
	bool padrao=true;
	for(int i=0; i<tabuleiro.size(); i++){
		for(int j=0; j<tabuleiro[i].size(); j++){
			padrao ? SDL_SetRenderDrawColor(renderer, 0, 180, 0, 255) : SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(renderer, &(tabuleiro[i][j]));
			padrao = !padrao;
		}
		if(tabuleiro[i].size()%2==0) padrao = !padrao;
	}
}

void mostrar_posicoes_tabuleiro(std::vector<std::vector<SDL_Rect>>& tabuleiro){
	for(int i=0; i<tabuleiro.size(); i++){
		for(int j=0; j<tabuleiro[i].size(); j++){
			printf("x%d: %d y%d: %d  ", i, tabuleiro[i][j].x, j, tabuleiro[i][j].y);
		}
		printf("\n");
	}
}

void desenhar_peca(SDL_Rect& retangulo, int peca){
    std::string caminho = "assets/pecas/";
    std::string extensao = ".png";
    std::string nome_peca;

    switch(peca){
		case Vazio:           nome_peca = "Vazio";           break;
        case Agua:            nome_peca = "Agua";            break;
        case Borda:           nome_peca = "Borda";           break;
		case BlackPawn:       nome_peca = "BlackPawn";       break;
        case BlackKnight:     nome_peca = "BlackKnight";     break;
        case BlackBishop:     nome_peca = "BlackBishop";     break;
        case BlackRook:       nome_peca = "BlackRook";       break;
        case BlackQueen:      nome_peca = "BlackQueen";      break;
        case BlackKing:       nome_peca = "BlackKing";       break;
        case WhitePawn:       nome_peca = "WhitePawn";       break;
        case WhiteKnight:     nome_peca = "WhiteKnight";     break;
        case WhiteBishop:     nome_peca = "WhiteBishop";     break;
        case WhiteRook:       nome_peca = "WhiteRook";       break;
        case WhiteQueen:      nome_peca = "WhiteQueen";      break;
        case WhiteKing:       nome_peca = "WhiteKing";       break;
		default:
			printf("Erro ao desenhar peca: %d", peca); exit(1);
    }

	if(nome_peca.compare("Vazio")!=0){
		std::string caminho_completo = caminho + nome_peca + extensao;
		SDL_Surface* peca_sur = IMG_Load(caminho_completo.c_str());
		SDL_Texture* peca_tex = SDL_CreateTextureFromSurface(renderer, peca_sur);
		SDL_RenderCopy(renderer, peca_tex, NULL, &retangulo);

		SDL_FreeSurface(peca_sur);
	}
}

void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;	
}

void inverter_tabuleiro(std::vector<std::vector<int>>& tabuleiro, int eixo){
	//1 = horizontal, 2 = vertical, 3 = metade horizontal, 4 = metade vertical

	int dist_x=tabuleiro.size(), dist_y=tabuleiro.size();
	if(eixo==1){
		dist_x/=2;
	}
	else if(eixo==2){
		dist_y/=2;
	}
	else{
		dist_x/=2;
		dist_y/=2;
	}

	for(int i=0; i<dist_x; i++){
		for(int j=0; j<dist_y; j++){
			if(eixo == 1 || eixo == 3) swap(&(tabuleiro[i][j]), &(tabuleiro[tabuleiro.size()-1-i][j]));
			else swap(&(tabuleiro[i][j]), &(tabuleiro[i][tabuleiro.size()-1-j]));
		}
	}
}

void imprimir_tabuleiro(std::vector<std::vector<int>>& tabuleiro){
	for(int i=0; i<tabuleiro.size()/2; i++){
		for(int j=0; j<tabuleiro[i].size()/2; j++){
			printf("%d ", tabuleiro[i][j]);
		}
		printf("\n");
	}
}

void imprimir_lances(std::vector<Lance>& lances){
	int total_lances = lances.size();

	for(int i=total_lances-1; i>=0; i--){
		printf("Origem: %d %d Destino: %d %d\n", lances[i].src_i, lances[i].src_j, lances[i].dst_i, lances[i].dst_j);
	}
	printf("Total lances: %d\n\n", total_lances);
}

void limpar_lances(std::vector<Lance>& lances){
	int total_lances = lances.size();

	for(int i=total_lances-1; i>=0; i--){
		lances.pop_back();
	}
}

int main(int argc, char* argv[]) {
	requiem:
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
	int inicio_x=30;
	int inicio_y=50;
	int casas_por_linha = 8;
	int tam_quadrado = 60;

	int final_x = inicio_x + (casas_por_linha)*tam_quadrado;
	int final_y = inicio_y + (casas_por_linha)*tam_quadrado;

	std::vector<std::vector<SDL_Rect>> tabuleiro = criar_tabuleiro(casas_por_linha, inicio_x, inicio_y, tam_quadrado);
	
	/*
	std::vector<std::vector<int>> pecas_tabuleiro = {
		{BlackRook, BlackKnight, BlackBishop, BlackKing, BlackQueen, BlackBishop, BlackKnight, BlackRook},
		{BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn},
		{Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio},
		{Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio},
		{Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio},
		{Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio},
		{WhitePawn, WhitePawn, WhitePawn, WhitePawn, WhitePawn, WhitePawn, WhitePawn, WhitePawn},
		{WhiteRook, WhiteKnight, WhiteBishop, WhiteKing, WhiteQueen, WhiteBishop, WhiteKnight, WhiteRook},
	};
	*/
	/*
	std::vector<std::vector<int>> pecas_tabuleiro = {
		{BlackRook, BlackKnight, BlackBishop, BlackKing, BlackQueen, BlackBishop, Vazio, Vazio},
		{BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, WhiteRook},
		{BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn},
		{BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn},
		{Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio},
		{Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio},
		{WhiteQueen, WhiteQueen, WhiteQueen, WhiteQueen, WhiteQueen, WhiteQueen, WhiteQueen, WhiteQueen},
		{WhiteQueen, WhiteKnight, WhiteBishop, WhiteQueen, WhiteQueen, WhiteBishop, WhiteKnight, WhiteQueen},
	};
	*/
	std::vector<std::vector<int>> pecas_tabuleiro = {
		{BlackRook, BlackKnight, BlackBishop, BlackKing, BlackQueen, BlackBishop, Vazio, Vazio},
		{BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, Vazio},
		{BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, Vazio, Vazio},
		{BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, BlackPawn, Vazio},
		{Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, WhiteRook},
		{Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio},
		{WhiteQueen, WhiteQueen, WhiteQueen, WhiteQueen, WhiteQueen, WhiteQueen, WhiteQueen, WhiteQueen},
		{WhiteQueen, WhiteKnight, WhiteBishop, WhiteQueen, WhiteQueen, WhiteBishop, WhiteKnight, WhiteQueen},
	};

	std::vector<Lance> lances;

	SDL_Event evento;
	int rodar=1;
	bool sentido_brancas=true;

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
					case 'w': inverter_tabuleiro(pecas_tabuleiro, 3); imprimir_tabuleiro(pecas_tabuleiro); break;
					case 's': inverter_tabuleiro(pecas_tabuleiro, 4); imprimir_tabuleiro(pecas_tabuleiro); break;
					case 'a': inverter_tabuleiro(pecas_tabuleiro, 1); imprimir_tabuleiro(pecas_tabuleiro); break;
					case 'd': inverter_tabuleiro(pecas_tabuleiro, 2); imprimir_tabuleiro(pecas_tabuleiro); break;
					case 'r': goto requiem;
					case 'l':
						lances = todos_possiveis_lances(pecas_tabuleiro);
						imprimir_lances(lances);
						limpar_lances(lances);
						printf("\n");
						break;

					case 'k':
						lances = todos_possiveis_lances(pecas_tabuleiro);
						if(lances.size()!=0){
							executar_lance(pecas_tabuleiro, lances[rand()%lances.size()]);
						}
						imprimir_lances(lances);
						limpar_lances(lances);
						printf("\n");
						break;
					
					case 'o': sentido_brancas = !sentido_brancas;
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

		desenhar_tabuleiro(tabuleiro);

		if(sentido_brancas){
			for(int i=0; i<pecas_tabuleiro.size(); i++){
				for(int j=0; j<pecas_tabuleiro[i].size(); j++){
					desenhar_peca(tabuleiro[i][j], pecas_tabuleiro[i][j]);
				}
			}
		}
		else{
			for(int i=0; i<pecas_tabuleiro.size(); i++){
				for(int j=0; j<pecas_tabuleiro[i].size(); j++){
					desenhar_peca(tabuleiro[i][j], pecas_tabuleiro[(int) pecas_tabuleiro[i].size()-1-i][j]);
				}
			}
		}		
		
		SDL_RenderPresent(renderer);

		SDL_Delay(100);
	}

	//liberar memoria de som.h
	quitMixer();

	return 0;
}

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <cstdio>
#include "pecas.h"
#include "menu.h"
#include "visual.h"
#include "ia.h"
#include "main.h"

const int WIDTH = 1080, HEIGHT = 640;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void operacoes_clicar(int i, int j, std::vector<Lance>& lances_clicado, 
	std::vector<std::vector<char>>& pecas_tabuleiro, std::vector<FEN>& controle_lances, int& turno){
	static int clique = Selecionar;
	int peca = pecas_tabuleiro[i][j];

	bool cor_valida=true;

	if(turno == White){
		cor_valida = branco(peca);
	}
	else if(turno == Black){
		cor_valida = preto(peca);
	}

	printf("i: %d j: %d\n", i, j);
	//playSound(sound);
	
	if(clique == Selecionar){
		printf("Selecionar\n");
		limpar_lances(lances_clicado);
		if(cor_valida && peca!=Vazio && peca!=Agua){
			lances_clicado = possiveis_lances_peca({i, j}, pecas_tabuleiro, &controle_lances);
			imprimir_lances(lances_clicado);
			clique = Executar;
		}
	}
	else if(clique == Executar){
		printf("Executar\n");
		printf("total lances_clicado: %d\n", (int) lances_clicado.size());
		bool executado=false;
		for(int contador=0; contador<lances_clicado.size(); contador++){
			if(lances_clicado[contador].dst_i == i && lances_clicado[contador].dst_j == j){
				printf("Execuntando lance\n");
				executado = true;

				//int org_i = lances_clicado[contador].src_i;
				//int org_j = lances_clicado[contador].src_j;
				//controle_lances.push_back({lances_clicado[contador], pecas_tabuleiro[i][j], pecas_tabuleiro[org_i][org_j]});
				
				executar_lance(pecas_tabuleiro, lances_clicado[contador], &controle_lances);
				if(turno==White) turno=Black;
				else if(turno==Black) turno=White;

				if(EstaEmCheque(pecas_tabuleiro, turno)){
					printf("Cheque\n");
				}
				break;
			}
		}

		limpar_lances(lances_clicado);
		clique = Selecionar;

		//Seleciona peca clicada se nao tiver executado um lance no ultimo clique
		if(executado==false){
			operacoes_clicar(i, j, lances_clicado, pecas_tabuleiro, controle_lances, turno);
		}
	}
}

void jogar_computador(int i, int j, std::vector<Lance>& lances_clicado, 
	std::vector<std::vector<char>>& pecas_tabuleiro, std::vector<FEN>& controle_lances, int& turno){
	static int clique = Selecionar;
	int peca = pecas_tabuleiro[i][j];

	bool cor_valida=true;

	if(turno == White){
		cor_valida = branco(peca);
	}
	else if(turno == Black){
		cor_valida = preto(peca);
	}

	printf("i: %d j: %d\n", i, j);
	//playSound(sound);
	
	if(clique == Selecionar){
		printf("Selecionar\n");
		limpar_lances(lances_clicado);
		if(cor_valida && peca!=Vazio && peca!=Agua){
			lances_clicado = possiveis_lances_peca({i, j}, pecas_tabuleiro, &controle_lances);
			imprimir_lances(lances_clicado);
			clique = Executar;
		}
	}
	else if(clique == Executar){
		printf("Executar\n");
		printf("total lances_clicado: %d\n", (int) lances_clicado.size());
		bool executado=false;
		for(int contador=0; contador<lances_clicado.size(); contador++){
			if(lances_clicado[contador].dst_i == i && lances_clicado[contador].dst_j == j){
				printf("Execuntando lance\n");
				executado = true;

				//int org_i = lances_clicado[contador].src_i;
				//int org_j = lances_clicado[contador].src_j;
				//controle_lances.push_back({lances_clicado[contador], pecas_tabuleiro[i][j], pecas_tabuleiro[org_i][org_j]});
				
				executar_lance(pecas_tabuleiro, lances_clicado[contador], &controle_lances);
				if(turno==White) turno=Black;
				else if(turno==Black) turno=White;

				if(EstaEmCheque(pecas_tabuleiro, turno)){
					printf("Cheque\n");
				}
				break;
			}
		}

		limpar_lances(lances_clicado);
		clique = Selecionar;

		//Seleciona peca clicada se nao tiver executado um lance no ultimo clique
		if(executado==false){
			operacoes_clicar(i, j, lances_clicado, pecas_tabuleiro, controle_lances, turno);
		}
		else{
			int pseudo_turno = turno==White ? Black : White;
			executar_lance_ia(controle_lances, pecas_tabuleiro, pseudo_turno);
			turno = turno==White ? Black : White;
		}
	}
}

int main(int argc, char* argv[]) {
	
	//Criar Janela
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Xadrez",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
							  WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	//Variaveis de configuracao
	Menu myMenu = Menu(WIDTH, HEIGHT);
	int inicio_x=30;
	int inicio_y=50;
	int casas_por_linha = 8;
	int tam_quadrado = 60;

	int final_x = inicio_x + (casas_por_linha)*tam_quadrado;
	int final_y = inicio_y + (casas_por_linha)*tam_quadrado;

	std::vector<std::vector<SDL_Rect>> tabuleiro = criar_tabuleiro(casas_por_linha, inicio_x, inicio_y, tam_quadrado);
	
	std::vector<std::vector<char>> pecas_tabuleiro = {
		{BlackStaticRook, BlackKnight, BlackBishop, BlackQueen, BlackStaticKing, BlackBishop, BlackKnight, BlackStaticRook},
		{BlackStaticPawn, BlackStaticPawn, BlackStaticPawn, BlackStaticPawn, BlackStaticPawn, BlackStaticPawn, BlackStaticPawn, BlackStaticPawn},
		{Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio},
		{Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio},
		{Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio},
		{Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio},
		{WhiteStaticPawn, WhiteStaticPawn, WhiteStaticPawn, WhiteStaticPawn, WhiteStaticPawn, WhiteStaticPawn, WhiteStaticPawn, WhiteStaticPawn},
		{WhiteStaticRook, WhiteKnight, WhiteBishop, WhiteQueen, WhiteStaticKing, WhiteBishop, WhiteKnight, WhiteStaticRook},
	};

	/*
	std::vector<std::vector<char>> pecas_tabuleiro = {
		{Agua, Agua, Agua, Agua, Agua, Agua, Agua, Agua, Agua, Agua},
		{Agua, BlackStaticRook, BlackKnight, BlackBishop, BlackQueen, BlackStaticKing, BlackBishop, BlackKnight, BlackStaticRook, Agua},
		{Agua, BlackStaticPawn, BlackStaticPawn, BlackStaticPawn, BlackStaticPawn, BlackStaticPawn, BlackStaticPawn, BlackStaticPawn, BlackStaticPawn, Agua},
		{Agua, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Agua},
		{Agua, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Agua},
		{Agua, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Agua},
		{Agua, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Agua},
		{Agua, WhiteStaticPawn, WhiteStaticPawn, WhiteStaticPawn, WhiteStaticPawn, WhiteStaticPawn, WhiteStaticPawn, WhiteStaticPawn, WhiteStaticPawn, Agua},
		{Agua, WhiteStaticRook, WhiteKnight, WhiteBishop, WhiteQueen, WhiteStaticKing, WhiteBishop, WhiteKnight, WhiteStaticRook, Agua},
		{Agua, Agua, Agua, Agua, Agua, Agua, Agua, Agua, Agua, Agua},
	};
	*/

	/*
	std::vector<std::vector<char>> pecas_tabuleiro = {
		{Agua, Agua, Agua, Agua, Agua, Agua, Agua, Agua, Agua, Agua},
		{Agua, BlackQueen, BlackQueen, Vazio, Vazio, BlackStaticKing, BlackQueen, BlackQueen, Vazio, Agua},
		{Agua, BlackStaticPawn, Vazio, Vazio, Vazio, BlackQueen, BlackStaticPawn, Vazio, BlackStaticPawn, Agua},
		{Agua, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Agua},
		{Agua, Vazio, BlackPawn, Vazio, Vazio, Vazio, Vazio, BlackPawn, Vazio, Agua},
		{Agua, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, BlackQueen, Vazio, Agua},
		{Agua, Vazio, Vazio, WhitePawn, WhiteBishop, Vazio, Vazio, Vazio, Vazio, Agua},
		{Agua, WhiteStaticPawn, WhiteStaticPawn, Vazio, WhiteBishop, WhiteKnight, Vazio, Vazio, Vazio, Agua},
		{Agua, WhiteStaticRook, Vazio, Vazio, WhiteKing, Vazio, Vazio, Vazio, Vazio, Agua},
		{Agua, Agua, Agua, Agua, Agua, Agua, Agua, Agua, Agua, Agua},
	};
	*/
	/*
	//Jogo com Sofia
	std::vector<std::vector<char>> pecas_tabuleiro = {
		{BlackQueen, BlackQueen, Vazio, Vazio, BlackStaticKing, BlackQueen, BlackQueen, Vazio},
		{BlackStaticPawn, Vazio, Vazio, Vazio, BlackQueen, BlackStaticPawn, Vazio, BlackStaticPawn},
		{Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio},
		{Vazio, BlackPawn, Vazio, Vazio, Vazio, Vazio, BlackPawn, Vazio},
		{Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, BlackQueen, Vazio},
		{Vazio, Vazio, WhitePawn, WhiteBishop, Vazio, Vazio, Vazio, Vazio},
		{WhiteStaticPawn, WhiteStaticPawn, Vazio, WhiteBishop, WhiteKnight, Vazio, Vazio, Vazio},
		{WhiteStaticRook, Vazio, Vazio, WhiteKing, Vazio, Vazio, Vazio, Vazio},
	};
	*/

	std::vector<Lance> lances;
	std::vector<Lance> lances_clicado;
	std::vector<FEN> controle_lances;
	std::vector<SDL_Texture*> imagens;

	SDL_Event evento;
	bool rodar=true;
	int turno = White;
	bool sentido_brancas=true;
	bool inverter=false;
	iniciar_imagens(&renderer, imagens);

	//Carrega a tela de inicio
	menu_principal:
	myMenu.menu_principal(&renderer, &rodar);

	//Execucao do jogo
	while(rodar){
		while(SDL_PollEvent(&evento)){
			if(evento.type == SDL_QUIT) rodar=0;

			else if(evento.type == SDL_KEYDOWN){
				switch(evento.key.keysym.sym){
					case SDLK_ESCAPE:
						if(myMenu.menu_pausa(&renderer, &rodar)) goto menu_principal;
						break;
					//case 'q': playSound(sound);	break;
					case 'w': inverter_tabuleiro(pecas_tabuleiro, 3); imprimir_tabuleiro(pecas_tabuleiro); break;
					case 's': inverter_tabuleiro(pecas_tabuleiro, 4); imprimir_tabuleiro(pecas_tabuleiro); break;
					case 'a': inverter_tabuleiro(pecas_tabuleiro, 1); imprimir_tabuleiro(pecas_tabuleiro); break;
					case 'd': inverter_tabuleiro(pecas_tabuleiro, 2); imprimir_tabuleiro(pecas_tabuleiro); break;
					case 'l':
						lances = todos_possiveis_lances(pecas_tabuleiro, turno, &controle_lances);
						imprimir_lances(lances);
						limpar_lances(lances);
						printf("\n");
						break;

					case 'k':
						lances = todos_possiveis_lances(pecas_tabuleiro, turno, &controle_lances);
						if(lances.size()!=0){
							executar_lance(pecas_tabuleiro, lances[rand()%lances.size()], &controle_lances);
						}
						if(turno == White) turno = Black;
						else if(turno == Black) turno = White;
						imprimir_lances(lances);
						limpar_lances(lances);
						printf("\n");
						break;
					
					case 'o': sentido_brancas = !sentido_brancas; inverter = !inverter; break;
					case 'z': 
						reverter_lance(controle_lances, pecas_tabuleiro, turno); 
						if(ModoDeJogo==Computador) reverter_lance(controle_lances, pecas_tabuleiro, turno);
						break;
					case 'x': mostrar_FEN(controle_lances); break;
					case ']': 
						do{
							SDL_PollEvent(&evento);
						} while(evento.type != SDL_KEYDOWN);
					case 'v':
						printf("Valor posicao: %d\n", avaliacao_posicao(pecas_tabuleiro));
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
					int j = (pos_x-inicio_x)/tam_quadrado;
					int i = (pos_y-inicio_y)/tam_quadrado;
					if(inverter) i = pecas_tabuleiro.size()-1-i;
					
					if (ModoDeJogo==Player)operacoes_clicar(i, j, lances_clicado, pecas_tabuleiro, controle_lances, turno);
					else if(ModoDeJogo==Computador) jogar_computador(i, j, lances_clicado, pecas_tabuleiro, controle_lances, turno);
				}
			}
		}
		//Carregar plano de fundo
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderClear(renderer);

		desenhar_tabuleiro(&renderer, tabuleiro, inverter);

		if(sentido_brancas){
			for(int i=0; i<pecas_tabuleiro.size(); i++){
				for(int j=0; j<pecas_tabuleiro[i].size(); j++){
					carregar_imagens(&renderer, imagens, tabuleiro[i][j], pecas_tabuleiro[i][j]);
				}
			}
		}
		else{
			for(int i=0; i<pecas_tabuleiro.size(); i++){
				for(int j=0; j<pecas_tabuleiro[i].size(); j++){
					carregar_imagens(&renderer, imagens, tabuleiro[i][j], pecas_tabuleiro[(int) pecas_tabuleiro[i].size()-1-i][j]);
				}
			}
		}

		if(lances_clicado.size()!=0){
			highlight_possiveis_lances(&renderer, lances_clicado, pecas_tabuleiro, tabuleiro, inverter);
		}
		
		SDL_RenderPresent(renderer);

		SDL_Delay(120);
	}
	
	//Liberando texturas
	destruir_imagens(imagens);
	
	//Liberando memoria e subsistemas
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	//liberar memoria de som.h
	//
	//quitMixer();

	return 0;
}

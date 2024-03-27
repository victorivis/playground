#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <cstdio>
#include "pecas.h"
#include "menu.h"
#include "main.h"

const int WIDTH = 1080, HEIGHT = 640;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void highlight_proximo_lance(SDL_Rect posicao, bool capturar){
	if(capturar){
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 180);
	}
	else{
		SDL_SetRenderDrawColor(renderer, 180, 180, 180, 180);
	}

	posicao.x += posicao.w/4;
	posicao.y += posicao.h/4;
	posicao.w/=2;
	posicao.h/=2;

	SDL_RenderFillRect(renderer, &posicao);
}

void highlight_possiveis_lances(std::vector<Lance>& lances, std::vector<std::vector<char>>& pecas_tabuleiro, std::vector<std::vector<SDL_Rect>>& quadrado_tabuleiro, bool inverter){
	for(int i=0; i<lances.size(); i++){
		if(!inverter){
			char peca = pecas_tabuleiro[lances[i].dst_i][lances[i].dst_j];
			highlight_proximo_lance(quadrado_tabuleiro[lances[i].dst_i][lances[i].dst_j], peca!=Vazio && peca!=Agua);
		}
		else{
			char peca = pecas_tabuleiro[lances[i].dst_i][lances[i].dst_j];
			highlight_proximo_lance(quadrado_tabuleiro[pecas_tabuleiro.size()-1-lances[i].dst_i][lances[i].dst_j], peca!=Vazio && peca!=Agua);
		}
	}
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

void desenhar_tabuleiro(std::vector<std::vector<SDL_Rect>>& tabuleiro, bool padrao){
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

void mostrar_pecas_tabuleiro(std::vector<std::vector<char>>& pecas_tabuleiro){
	for(int i=0; i<pecas_tabuleiro.size(); i++){
		printf("{");
		for(int j=0; j<pecas_tabuleiro[i].size(); j++){
			printf("%d", pecas_tabuleiro[i][j]);
			if(j!=(int) pecas_tabuleiro[i].size()-1) printf(", ");
		}
		printf("},\n");
	}
}

SDL_Texture* desenhar_peca(char peca){
    std::string caminho = "assets/pecasBMP/";
    std::string extensao = ".bmp";
    std::string nome_peca;

    switch(peca){
		case Vazio:           nome_peca = "Vazio";           break;
        case Agua:            nome_peca = "Agua";            break;
        case Borda:           nome_peca = "Borda";           break;

		case BlackStaticPawn:
		case BlackPawn:       nome_peca = "BlackPawn";       break;
        case BlackKnight:     nome_peca = "BlackKnight";     break;
        case BlackBishop:     nome_peca = "BlackBishop";     break;
		case BlackStaticRook:
        case BlackRook:       nome_peca = "BlackRook";       break;
        case BlackQueen:      nome_peca = "BlackQueen";      break;
		case BlackStaticKing:
        case BlackKing:       nome_peca = "BlackKing";       break;

		case WhiteStaticPawn:
        case WhitePawn:       nome_peca = "WhitePawn";       break;
        case WhiteKnight:     nome_peca = "WhiteKnight";     break;
        case WhiteBishop:     nome_peca = "WhiteBishop";     break;
		case WhiteStaticRook:
        case WhiteRook:       nome_peca = "WhiteRook";       break;
        case WhiteQueen:      nome_peca = "WhiteQueen";      break;
		case WhiteStaticKing:
        case WhiteKing:       nome_peca = "WhiteKing";       break;
		default:
			printf("Erro ao desenhar peca: %d\n", peca); exit(1);
    }

	if(nome_peca.compare("Vazio")!=0 && nome_peca.compare("Borda")!=0){
		std::string caminho_completo = caminho + nome_peca + extensao;
		SDL_Surface* peca_sur = SDL_LoadBMP(caminho_completo.c_str());
		SDL_Texture* peca_tex = SDL_CreateTextureFromSurface(renderer, peca_sur);
		//SDL_RenderCopy(renderer, peca_tex, NULL, &retangulo);

		SDL_FreeSurface(peca_sur);
		//SDL_DestroyTexture(peca_tex);
		return peca_tex;
	}
	else{
		return nullptr;
	}
}

void iniciar_imagens(std::vector<SDL_Texture*>& imagens){
	for(char i=Agua; i<=WhiteKing; i++){
		imagens.push_back(desenhar_peca(i));
	}
}

void carregar_imagens(std::vector<SDL_Texture*>& imagens, SDL_Rect& posicao, char peca){
	if(peca>=0 && peca<imagens.size()){
		SDL_RenderCopy(renderer, imagens[peca], NULL, &posicao);
	}
}

void destruir_imagens(std::vector<SDL_Texture*>& imagens){
	int total = (int) imagens.size()-1;
	for(int i=total; i>=0; i--){
		SDL_DestroyTexture(imagens[i]);
		imagens.pop_back();
	}
}

void swap(auto* a, auto* b){
	auto temp = *a;
	*a = *b;
	*b = temp;	
}

void inverter_tabuleiro(std::vector<std::vector<char>>& tabuleiro, int eixo){
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

void imprimir_tabuleiro(std::vector<std::vector<char>>& tabuleiro){
	for(int i=0; i<tabuleiro.size()/2; i++){
		for(int j=0; j<tabuleiro[i].size()/2; j++){
			printf("%d ", tabuleiro[i][j]);
		}
		printf("\n");
	}
}

void imprimir_lances(std::vector<Lance>& lances){
	int total_lances = (int) lances.size();

	for(int i=0; i<total_lances; i++){
		printf("Origem: %d %d Destino: %d %d\n", lances[i].src_i, lances[i].src_j, lances[i].dst_i, lances[i].dst_j);
	}
	printf("Total de lances possiveis: %d\n\n", total_lances);
}

void limpar_lances(std::vector<Lance>& lances){
	int total_lances = lances.size();

	for(int i=0; i<total_lances; i++){
		lances.pop_back();
	}
}

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

int main(int argc, char* argv[]) {
	
	//Criar Janela
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Xadrez",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
							  WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	//iniciar biblioteca som.h
	//
	//initMixer();
	//int sound = loadSound("assets/move-self.mp3");
	//int som_captura = loadSound("assets/capture.mp3");
	//setVolume(30);

	//Variaveis de configuracao
	Menu myMenu = Menu(WIDTH, HEIGHT);
	int inicio_x=30;
	int inicio_y=20;
	int casas_por_linha = 10;
	int tam_quadrado = 60;

	int final_x = inicio_x + (casas_por_linha)*tam_quadrado;
	int final_y = inicio_y + (casas_por_linha)*tam_quadrado;

	std::vector<std::vector<SDL_Rect>> tabuleiro = criar_tabuleiro(casas_por_linha, inicio_x, inicio_y, tam_quadrado);
	
	/*
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
	*/

	std::vector<std::vector<char>> pecas_tabuleiro = {
		{Agua, Agua, Agua, Agua, Agua, Agua, Agua, Agua, Agua, Agua},
		{Agua, BlackStaticRook, BlackKnight, BlackBishop, BlackQueen, BlackStaticKing, BlackBishop, BlackKnight, BlackStaticRook, Agua},
		{Agua, BlackStaticPawn, BlackStaticPawn, BlackStaticPawn, BlackStaticPawn, BlackStaticPawn, BlackStaticPawn, BlackStaticPawn, BlackStaticPawn, Agua},
		{Agua, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Agua},
		{Agua, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Agua},
		{Agua, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Agua},
		{Agua, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Vazio, Agua},
		{Agua, WhiteStaticPawn, Vazio, WhiteStaticPawn, WhiteStaticPawn, WhiteStaticPawn, WhiteStaticPawn, WhiteStaticPawn, WhiteStaticPawn, Agua},
		{Agua, WhiteStaticRook, WhiteKnight, WhiteBishop, WhiteQueen, WhiteStaticKing, WhiteBishop, WhiteKnight, WhiteStaticRook, Agua},
		{Agua, Agua, Agua, Agua, Agua, Agua, Agua, Agua, Agua, Agua},
	};

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
	iniciar_imagens(imagens);

	//Carrega a tela de inicio
	menu_principal:
	myMenu.menu_principal(&renderer, &rodar);

	salvar_configuracoes("generico.txt");
	//escrever_configuracoes("file.txt");
	//ler_configuracoes("jones.txt");

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

					case 'p': mostrar_pecas_tabuleiro(pecas_tabuleiro);	break;
					case 'o': sentido_brancas = !sentido_brancas; inverter = !inverter; break;
					case 'z': reverter_lance(controle_lances, pecas_tabuleiro, turno); break;
					case 'x': mostrar_FEN(controle_lances); break;
					case ']': 
						do{
							SDL_PollEvent(&evento);
						} while(evento.type != SDL_KEYDOWN);
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
					operacoes_clicar(i, j, lances_clicado, pecas_tabuleiro, controle_lances, turno);
				}
			}
		}
		//Carregar plano de fundo
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderClear(renderer);

		desenhar_tabuleiro(tabuleiro, inverter);

		if(sentido_brancas){
			for(int i=0; i<pecas_tabuleiro.size(); i++){
				for(int j=0; j<pecas_tabuleiro[i].size(); j++){
					carregar_imagens(imagens, tabuleiro[i][j], pecas_tabuleiro[i][j]);
				}
			}
		}
		else{
			for(int i=0; i<pecas_tabuleiro.size(); i++){
				for(int j=0; j<pecas_tabuleiro[i].size(); j++){
					carregar_imagens(imagens, tabuleiro[i][j], pecas_tabuleiro[(int) pecas_tabuleiro[i].size()-1-i][j]);
				}
			}
		}

		if(lances_clicado.size()!=0){
			highlight_possiveis_lances(lances_clicado, pecas_tabuleiro, tabuleiro, inverter);
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

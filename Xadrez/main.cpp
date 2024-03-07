#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <cstdio>
#include "main.h"

#define branco(peca) (peca>=WhitePawn && peca<=WhiteKing)
#define preto(peca) (peca>=BlackPawn && peca<=BlackKing)

const int WIDTH = 1080, HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

char calcular_destino(int direcao, std::pair<char, char> origem, std::vector<std::vector<char>>& tabuleiro, int num_movimentos){
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

		case CimaDireita:
			return tabuleiro[origem.first-2][origem.second+1];

		case CimaEsquerda:
			return tabuleiro[origem.first-2][origem.second-1];

		case BaixoDireita:
			return tabuleiro[origem.first+2][origem.second+1];

		case BaixoEsquerda:
			return tabuleiro[origem.first+2][origem.second-1];

		case DireitaCima:
			return tabuleiro[origem.first-1][origem.second+2];

		case DireitaBaixo:
			return tabuleiro[origem.first+1][origem.second+2];

		case EsquerdaCima:
			return tabuleiro[origem.first-1][origem.second-2];

		case EsquerdaBaixo:
			return tabuleiro[origem.first+1][origem.second-2];
		
		default:
			printf("Erro! direcao impossivel: %d\n", direcao);
			exit(1);
	}

	return -1;
}

void executar_lance(std::vector<std::vector<char>>& tabuleiro, Lance& lance, std::vector<FEN>* controle_lances){
	//Previne de acessar memoria indevida
	if(lance.src_i<0 || lance.src_i>=tabuleiro.size()) printf("%d %d %d %d\n", lance.src_i, lance.src_j, lance.dst_i, lance.dst_j), exit(404);
	if(lance.src_j<0 || lance.src_j>=tabuleiro.size()) printf("%d %d %d %d\n", lance.src_i, lance.src_j, lance.dst_i, lance.dst_j), exit(404);
	if(lance.dst_i<0 || lance.dst_i>=tabuleiro.size()) printf("%d %d %d %d\n", lance.src_i, lance.src_j, lance.dst_i, lance.dst_j), exit(404);
	if(lance.dst_j<0 || lance.dst_j>=tabuleiro.size()) printf("%d %d %d %d\n", lance.src_i, lance.src_j, lance.dst_i, lance.dst_j), exit(404);
	
	int origem = tabuleiro[lance.src_i][lance.src_j];
	int roque=0;

	//Salva lance se for passado um vetor
	if(controle_lances != NULL){
		(*controle_lances).push_back({lance, tabuleiro[lance.dst_i][lance.dst_j], tabuleiro[lance.src_i][lance.src_j]});
	}

	//Detecta se a peca ja se moveu alguma vez
	switch(origem){
		case BlackStaticPawn: tabuleiro[lance.src_i][lance.src_j] = BlackPawn; break;
		case WhiteStaticPawn: tabuleiro[lance.src_i][lance.src_j] = WhitePawn; break;
		case BlackStaticRook: tabuleiro[lance.src_i][lance.src_j] = BlackRook; break;
		case WhiteStaticRook: tabuleiro[lance.src_i][lance.src_j] = WhiteRook; break;

		case BlackStaticKing:
			if(lance.src_j-lance.dst_j==2) roque=Oeste;
			else if(lance.src_j-lance.dst_j==-2) roque=Leste;
			tabuleiro[lance.src_i][lance.src_j] = BlackKing;
			break;

		case WhiteStaticKing:
			if(lance.src_j-lance.dst_j==2) roque=Oeste;
			else if(lance.src_j-lance.dst_j==-2) roque=Leste;
			tabuleiro[lance.src_i][lance.src_j] = WhiteKing;
			break;
	}

	//Propriamente faz o movimento
	tabuleiro[lance.dst_i][lance.dst_j] = tabuleiro[lance.src_i][lance.src_j];
    tabuleiro[lance.src_i][lance.src_j] = Vazio;

	
	if(roque==Oeste){
		std::pair<char, char> origem_rei = {lance.src_i, lance.src_j};
		int contador=1;
		char destino = calcular_destino(Oeste, origem_rei, tabuleiro, contador);
		while((destino!=BlackStaticRook && destino != WhiteStaticRook) && contador<tabuleiro.size()){
			contador++;
			destino = calcular_destino(Oeste, origem_rei, tabuleiro, contador);
		}
		std::pair<char, char> origem_torre = par_mover_direcao(Oeste, origem_rei, contador);
		std::pair<char, char> destino_torre = par_mover_direcao(Oeste, origem_rei, 1);

		Lance torre = {origem_torre.first, origem_torre.second, destino_torre.first, destino_torre.second};
		executar_lance(tabuleiro, torre, controle_lances);
		printf("Rei Rocou! Esquerda\n");
	}
	else if(roque==Leste){
		std::pair<char, char> origem_rei = {lance.src_i, lance.src_j};
		int contador=1;
		char destino = calcular_destino(Leste, origem_rei, tabuleiro, contador);
		while((destino!=BlackStaticRook && destino != WhiteStaticRook) && contador<tabuleiro.size()){
			contador++;
			destino = calcular_destino(Leste, origem_rei, tabuleiro, contador);
		}
		std::pair<char, char> origem_torre = par_mover_direcao(Leste, origem_rei, contador);
		std::pair<char, char> destino_torre = par_mover_direcao(Leste, origem_rei, 1);

		Lance torre = {origem_torre.first, origem_torre.second, destino_torre.first, destino_torre.second};
		executar_lance(tabuleiro, torre, controle_lances);
		printf("Rei Rocou! Direita\n");
	}

	//Promocao de peao
	if(lance.dst_i == tabuleiro.size()-1 && tabuleiro[lance.dst_i][lance.dst_j]==BlackPawn){
		tabuleiro[lance.dst_i][lance.dst_j]=BlackQueen;
	}
	else if(lance.dst_i == 0 && tabuleiro[lance.dst_i][lance.dst_j]==WhitePawn){
		tabuleiro[lance.dst_i][lance.dst_j]=WhiteQueen;
	}
}

//Refatorar esse codigo
bool movimento_permitido(int direcao, int tipo_lance, std::vector<std::vector<char>>& tabuleiro, std::pair<char, char> origem, int num_movimentos){
    int tamanho = tabuleiro.size();
    bool saida;
	
	char peca = tabuleiro[origem.first][origem.second];

	bool eh_branca;
	if(branco(peca)) eh_branca=true;
	else if(preto(peca)) eh_branca=false;
	else return false;

	int capturar=tipo_lance;
	if(tipo_lance == Capturar || tipo_lance == MoverCapturar || tipo_lance == Pulo || tipo_lance == Roque){
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
			
		case CimaDireita:
			(origem.first-2 >= 0 && origem.second+1 < tamanho) ?
				saida=true : saida=false; break;

		case CimaEsquerda:
			(origem.first-2 >= 0 && origem.second-1 >= 0) ?
				saida=true : saida=false; break;

		case BaixoDireita:
			(origem.first+2 < tamanho && origem.second+1 < tamanho) ?
				saida = true : saida=false; break;

		case BaixoEsquerda:
			(origem.first+2 < tamanho && origem.second-1 >=0 ) ?
				saida = true : saida=false; break;

		case DireitaCima:
			(origem.first-1 >= 0 && origem.second+2 < tamanho) ?
				saida = true : saida=false; break;

		case DireitaBaixo:
			(origem.first+1 < tamanho && origem.second+2 < tamanho) ?
				saida = true : saida=false; break;

		case EsquerdaCima:
			(origem.first-1 >= 0 && origem.second-2 >= 0) ?
				saida = true : saida = false; break;

		case EsquerdaBaixo:
			(origem.first+1 < tamanho && origem.second-2 >= 0) ?
				saida = true : saida = false; break;
    }

	if(tipo_lance==Roque && saida){
		char destino = calcular_destino(direcao, origem, tabuleiro, num_movimentos);
		if(eh_branca){
			return destino==WhiteStaticRook;
		}
		else{
			return destino==BlackStaticRook;
		}
	}	
    if(capturar==Capturar && saida){
		//printf("If captura");
		char destino = calcular_destino(direcao, origem, tabuleiro, num_movimentos);
		if(tipo_lance==MoverCapturar || tipo_lance == Pulo){
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
		//printf("If mover");
		return saida;
	}
}

std::pair<char, char> par_mover_direcao(int direcao, std::pair<char, char>& origem, int num_movimentos){
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
		
		//Nao depende de num_movimentos ainda
		case CimaDireita:
			return {origem.first-2, origem.second+1};

		case CimaEsquerda:
			return {origem.first-2, origem.second-1};

		case BaixoDireita:
			return {origem.first+2, origem.second+1};

		case BaixoEsquerda:
			return {origem.first+2, origem.second-1};

		case DireitaCima:
			return {origem.first-1, origem.second+2};

		case DireitaBaixo:
			return {origem.first+1, origem.second+2};

		case EsquerdaCima:
			return {origem.first-1, origem.second-2};

		case EsquerdaBaixo:
			return {origem.first+1, origem.second-2};
	}

	//Isso provavelmente quebra o codigo
	exit(1);
	return {-1, -1};
}

Lance mover_direcao(int direcao, std::pair<char, char> origem, int num_movimentos){
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

		//Nao depende de num_movimentos ainda
		case CimaDireita:
			return {origem.first, origem.second, origem.first-2, origem.second+1};

		case CimaEsquerda:
			return {origem.first, origem.second, origem.first-2, origem.second-1};

		case BaixoDireita:
			return {origem.first, origem.second, origem.first+2, origem.second+1};

		case BaixoEsquerda:
			return {origem.first, origem.second, origem.first+2, origem.second-1};

		case DireitaCima:
			return {origem.first, origem.second, origem.first-1, origem.second+2};

		case DireitaBaixo:
			return {origem.first, origem.second, origem.first+1, origem.second+2};

		case EsquerdaCima:
			return {origem.first, origem.second, origem.first-1, origem.second-2};

		case EsquerdaBaixo:
			return {origem.first, origem.second, origem.first+1, origem.second-2};
	}

	//Isso provavelmente quebra o codigo
	exit(1);
	return {-1, -1, -1, -1};
}

void sequencia_lances(std::vector<char>& direcoes, std::pair<char, char> origem, int tipo_lance, std::vector<Lance>& lances, std::vector<std::vector<char>>& tabuleiro, int num_movimentos){
	for(int i=0; i<direcoes.size(); i++){
		if(tipo_lance == Roque){
			int contador=1;
			while(movimento_permitido(direcoes[i], Mover, tabuleiro, origem, contador)){
				//printf("Origem: {%d %d}, contador: %d\n", origem.first, origem.second, contador);
				//lances.push_back(mover_direcao(direcoes[i], origem, contador));
				contador+=1;
			}
			if(movimento_permitido(direcoes[i], Roque, tabuleiro, origem, contador)){
				printf("Roque possivel!\n");
				lances.push_back(mover_direcao(direcoes[i], origem, 2));
			}
		}

		else if(tipo_lance == Linha){
			int contador=1;
			while(movimento_permitido(direcoes[i], Mover, tabuleiro, origem, contador)){
				//printf("Origem: {%d %d}, contador: %d\n", origem.first, origem.second, contador);
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

std::vector<Lance> possiveis_lances_peca(std::pair<char, char> origem, std::vector<std::vector<char>>& tabuleiro, std::vector<FEN>* controle_lances){
	std::vector<Lance> saida;
	std::vector<char> direcoes;

	switch(tabuleiro[origem.first][origem.second]){
		case BlackStaticPawn:
			direcoes = {Sul};
			sequencia_lances(direcoes, origem, Mover, saida, tabuleiro, 2);
			direcoes.pop_back();

        case BlackPawn:
			if(movimento_permitido(Sul, Mover, tabuleiro, origem))
				saida.push_back(mover_direcao(Sul, origem));
			
			direcoes = {Sudeste, Sudoeste};
			sequencia_lances(direcoes, origem, Capturar, saida, tabuleiro, 1);
			break;

		case WhiteStaticPawn:
			direcoes = {Norte};
			sequencia_lances(direcoes, origem, Mover, saida, tabuleiro, 2);
			direcoes.pop_back();
		
		case WhitePawn:
			if(movimento_permitido(Norte, Mover, tabuleiro, origem))
				saida.push_back(mover_direcao(Norte, origem));

			direcoes = {Nordeste, Noroeste};
			sequencia_lances(direcoes, origem, Capturar, saida, tabuleiro, 1);
			break;

		case BlackStaticKing:
		case WhiteStaticKing:
			direcoes = {Leste, Oeste};
			sequencia_lances(direcoes, origem, Roque, saida, tabuleiro, 2);

		case BlackKing:
		case WhiteKing:
			direcoes = {Norte, Sul, Leste, Oeste, Nordeste, Noroeste, Sudeste, Sudoeste};
			sequencia_lances(direcoes, origem, MoverCapturar, saida, tabuleiro, 1);
			break;

		case BlackStaticRook:
		case WhiteStaticRook:
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

		case BlackKnight:
		case WhiteKnight:
			direcoes = {CimaDireita, CimaEsquerda, BaixoDireita, BaixoEsquerda, DireitaCima, DireitaBaixo, EsquerdaCima, EsquerdaBaixo};
			sequencia_lances(direcoes, origem, Pulo, saida, tabuleiro, 1);
			break;
	}

	return saida;
}

std::vector<Lance> todos_possiveis_lances(std::vector<std::vector<char>>& tabuleiro, int cor, std::vector<FEN>* controle_lances){
	std::vector<Lance> saida;
	bool cor_certa=true;
	
	for(uint8_t i=0; i<tabuleiro.size(); i++){
		for(uint8_t j=0; j<tabuleiro[i].size(); j++){
			if(cor==Black){
				cor_certa = preto(tabuleiro[i][j]);
			}
			else if(cor==White){
				cor_certa = branco(tabuleiro[i][j]);
			}
			
			if(cor_certa){
				std::pair<char, char> origem = {i, j};
				std::vector<Lance> atual = possiveis_lances_peca(origem, tabuleiro);
				for(int k=0; k<atual.size(); k++){
					saida.push_back(atual[k]);
				}
			}
		}
	}
	
	return saida;
}

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

void reverter_lance(std::vector<FEN>& controle_lances, std::vector<std::vector<char>>& pecas_tabuleiro, int& turno){
	int posicao = (int) controle_lances.size()-1;

	if(posicao >= 1 && turno!=Both){
		int pseudo_turno = Both;
		char ultima_peca = controle_lances[posicao].origem;
		char penultima_peca = controle_lances[posicao-1].origem;

		printf("Ultima peca: %d %d\n", ultima_peca, penultima_peca);
		if(branco(ultima_peca) == branco(penultima_peca)){
			printf("Reverter Dois Lances\n");
			reverter_lance(controle_lances, pecas_tabuleiro, pseudo_turno);
			posicao--;
		}
	}

	if(posicao!=-1){
		Lance ultimo_lance = controle_lances[posicao].move;
		char peca_capturada = controle_lances[posicao].peca;
		char peca_origem = controle_lances[posicao].origem;

		pecas_tabuleiro[ultimo_lance.src_i][ultimo_lance.src_j] = peca_origem;
		pecas_tabuleiro[ultimo_lance.dst_i][ultimo_lance.dst_j] = peca_capturada;
		
		controle_lances.pop_back();
		
		if(turno == Black) turno = White;
		else if(turno == White) turno = Black;
	}
}

void mostrar_FEN(std::vector<FEN>& controle_lances){
	for(int i=0; i<controle_lances.size(); i++){
		Lance l = controle_lances[i].move;
		char peca = controle_lances[i].peca;
		printf("Origem: {%d, %d} Destino: {%d, %d} peca: %d\n", l.src_i, l.src_j, l.dst_i, l.dst_j, peca);
	}
	printf("\n");
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

void desenhar_peca(SDL_Rect& retangulo, char peca){
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

	if(nome_peca.compare("Vazio")!=0 && nome_peca.compare("Agua")!=0 && nome_peca.compare("Borda")!=0){
		std::string caminho_completo = caminho + nome_peca + extensao;
		SDL_Surface* peca_sur = SDL_LoadBMP(caminho_completo.c_str());
		SDL_Texture* peca_tex = SDL_CreateTextureFromSurface(renderer, peca_sur);
		SDL_RenderCopy(renderer, peca_tex, NULL, &retangulo);

		SDL_FreeSurface(peca_sur);
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
	printf("Total lances: %d\n\n", total_lances);
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
			lances_clicado = possiveis_lances_peca({i, j}, pecas_tabuleiro);
			imprimir_lances(lances_clicado);
			clique = Executar;
		}
	}
	else if(clique == Executar){
		printf("Executar\n");
		printf("total lances_clicado: %d\n", (int) lances_clicado.size());
		bool executado=false;
		for(int contador=0; contador<lances_clicado.size(); contador++){
			printf("%d == %d && %d == %d\n",lances_clicado[contador].dst_i, i, lances_clicado[contador].dst_j, j);
			if(lances_clicado[contador].dst_i == i && lances_clicado[contador].dst_j == j){
				printf("Execuntando lance\n");
				executado = true;

				//int org_i = lances_clicado[contador].src_i;
				//int org_j = lances_clicado[contador].src_j;
				//controle_lances.push_back({lances_clicado[contador], pecas_tabuleiro[i][j], pecas_tabuleiro[org_i][org_j]});
				
				executar_lance(pecas_tabuleiro, lances_clicado[contador], &controle_lances);
				if(turno==White) turno=Black;
				else if(turno==Black) turno=White;
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

	std::vector<Lance> lances;
	std::vector<Lance> lances_clicado;
	std::vector<FEN> controle_lances;

	SDL_Event evento;
	int rodar=1;
	int turno = White;
	bool sentido_brancas=true;
	bool inverter=false;

	//Execucao do jogo
	while(rodar){
		while(SDL_PollEvent(&evento)){
			if(evento.type == SDL_QUIT) rodar=0;

			else if(evento.type == SDL_KEYDOWN){
				switch(evento.key.keysym.sym){
					case SDLK_ESCAPE:
						rodar=0;
						break;
					//case 'q': playSound(sound);	break;
					case 'w': inverter_tabuleiro(pecas_tabuleiro, 3); imprimir_tabuleiro(pecas_tabuleiro); break;
					case 's': inverter_tabuleiro(pecas_tabuleiro, 4); imprimir_tabuleiro(pecas_tabuleiro); break;
					case 'a': inverter_tabuleiro(pecas_tabuleiro, 1); imprimir_tabuleiro(pecas_tabuleiro); break;
					case 'd': inverter_tabuleiro(pecas_tabuleiro, 2); imprimir_tabuleiro(pecas_tabuleiro); break;
					case 'l':
						lances = todos_possiveis_lances(pecas_tabuleiro, Both);
						imprimir_lances(lances);
						limpar_lances(lances);
						printf("\n");
						break;

					case 'k':
						lances = todos_possiveis_lances(pecas_tabuleiro, Both);
						if(lances.size()!=0){
							executar_lance(pecas_tabuleiro, lances[rand()%lances.size()]);
						}
						imprimir_lances(lances);
						limpar_lances(lances);
						printf("\n");
						break;

					case 'p': mostrar_pecas_tabuleiro(pecas_tabuleiro);	break;
					case 'o': sentido_brancas = !sentido_brancas; inverter = !inverter; break;
					case 'z': reverter_lance(controle_lances, pecas_tabuleiro, turno); break;
					case 'x': mostrar_FEN(controle_lances); break;
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

		if(lances_clicado.size()!=0){
			highlight_possiveis_lances(lances_clicado, pecas_tabuleiro, tabuleiro, inverter);
		}
		
		SDL_RenderPresent(renderer);

		SDL_Delay(300);
	}

	//liberar memoria de som.h
	//
	//quitMixer();

	return 0;
}

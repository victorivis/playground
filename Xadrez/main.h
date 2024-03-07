#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <cstdio>

struct Lance{
	char src_i;
	char src_j;
	char dst_i;
	char dst_j;
};

struct FEN{
	Lance move;
	char peca;
	char origem;
};

enum Cor{
	Black, White, Both
};

enum Pecas{
	Vazio, Agua, Borda,
	BlackPawn, BlackStaticPawn, BlackKnight, BlackBishop, BlackRook, BlackStaticRook, BlackQueen, BlackStaticKing, BlackKing,
	WhitePawn, WhiteStaticPawn, WhiteKnight, WhiteBishop, WhiteRook, WhiteStaticRook, WhiteQueen, WhiteStaticKing, WhiteKing
};

enum Direcao{
    Norte, Sul, Leste, Oeste, Nordeste, Sudeste, Sudoeste, Noroeste, CimaDireita, CimaEsquerda, 
	BaixoDireita, BaixoEsquerda, DireitaCima, DireitaBaixo, EsquerdaCima, EsquerdaBaixo
};

enum Movimento{
	Linha=20, Pulo, Capturar, Mover, MoverCapturar, Seguro, Roque, EnPassant
};

enum Clique{
	Selecionar, Executar
};

char calcular_destino(int direcao, std::pair<char, char> origem, std::vector<std::vector<char>>& tabuleiro, int num_movimentos=1);
void executar_lance(std::vector<std::vector<char>>& tabuleiro, Lance& lance, std::vector<FEN>* controle_lances=NULL);
bool movimento_permitido(int direcao, int tipo_lance, std::vector<std::vector<char>>& tabuleiro, std::pair<char, char> origem, int num_movimentos=1);
std::pair<char, char> par_mover_direcao(int direcao, std::pair<char, char>& origem, int num_movimentos=1);
Lance mover_direcao(int direcao, std::pair<char, char> origem, int num_movimentos=1);
void sequencia_lances(std::vector<char>& direcoes, std::pair<char, char> origem, int tipo_lance, std::vector<Lance>& lances, std::vector<std::vector<char>>& tabuleiro, int num_movimentos);
std::vector<Lance> possiveis_lances_peca(std::pair<char, char> origem, std::vector<std::vector<char>>& tabuleiro, std::vector<FEN>* controle_lances=NULL);
std::vector<Lance> todos_possiveis_lances(std::vector<std::vector<char>>& tabuleiro, int cor, std::vector<FEN>* controle_lances=NULL);
void highlight_proximo_lance(SDL_Rect posicao, bool capturar);
void highlight_possiveis_lances(std::vector<Lance>& lances, std::vector<std::vector<char>>& pecas_tabuleiro, std::vector<std::vector<SDL_Rect>>& quadrado_tabuleiro, bool inverter);	
void reverter_lance(std::vector<FEN>& controle_lances, std::vector<std::vector<char>>& pecas_tabuleiro, int& turno);
void mostrar_FEN(std::vector<FEN>& controle_lances);
void desenhar_tabuleiro(std::vector<std::vector<SDL_Rect>>& tabuleiro, bool padrao);
void mostrar_posicoes_tabuleiro(std::vector<std::vector<SDL_Rect>>& tabuleiro);
void mostrar_pecas_tabuleiro(std::vector<std::vector<char>>& pecas_tabuleiro);
void desenhar_peca(SDL_Rect& retangulo, char peca);
void swap(auto* a, auto* b);
void inverter_tabuleiro(std::vector<std::vector<char>>& tabuleiro, int eixo);
void imprimir_tabuleiro(std::vector<std::vector<char>>& tabuleiro);
void limpar_lances(std::vector<Lance>& lances);
void operacoes_clicar(int i, int j, std::vector<Lance>& lances_clicado, 
std::vector<std::vector<char>>& pecas_tabuleiro, std::vector<FEN>& controle_lances, int& turno);
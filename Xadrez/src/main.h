#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>

enum Clique{
	Selecionar, Executar
};

void highlight_proximo_lance(SDL_Rect posicao, bool capturar);
void highlight_possiveis_lances(std::vector<Lance>& lances, std::vector<std::vector<char>>& pecas_tabuleiro, std::vector<std::vector<SDL_Rect>>& quadrado_tabuleiro, bool inverter);

void desenhar_tabuleiro(std::vector<std::vector<SDL_Rect>>& tabuleiro, bool padrao);
void mostrar_posicoes_tabuleiro(std::vector<std::vector<SDL_Rect>>& tabuleiro);
void mostrar_pecas_tabuleiro(std::vector<std::vector<char>>& pecas_tabuleiro);

SDL_Texture* desenhar_peca(char peca);
void iniciar_imagens(std::vector<SDL_Texture*>& imagens);
void carregar_imagens(std::vector<SDL_Texture*>& imagens, SDL_Rect& posicao, char peca);
void destruir_imagens(std::vector<SDL_Texture*>& imagens);

void swap(auto* a, auto* b);
void inverter_tabuleiro(std::vector<std::vector<char>>& tabuleiro, int eixo);
void imprimir_tabuleiro(std::vector<std::vector<char>>& tabuleiro);
void limpar_lances(std::vector<Lance>& lances);
void operacoes_clicar(int i, int j, std::vector<Lance>& lances_clicado, 
std::vector<std::vector<char>>& pecas_tabuleiro, std::vector<FEN>& controle_lances, int& turno);
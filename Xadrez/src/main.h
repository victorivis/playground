#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>

enum Clique{
	Selecionar, Executar
};

void operacoes_clicar(int i, int j, std::vector<Lance>& lances_clicado, 
std::vector<std::vector<char>>& pecas_tabuleiro, std::vector<FEN>& controle_lances, int& turno);
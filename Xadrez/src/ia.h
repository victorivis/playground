#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <cstdio>
#include <climits>
#include "pecas.h"
#include "menu.h"

const int profundidade=2;

enum valor_pecas{
    peao=1, cavalo=3, bispo=3, torre=5, rainha=9, rei=900
};

int retorna_valor(char peca);
int avaliacao_posicao(std::vector<std::vector<char>>& pecas_tabuleiro);
Lance minmax(std::vector<FEN>& controle_lances, std::vector<std::vector<char>>& pecas_tabuleiro, int& turno, bool max);
void executar_lance_ia(std::vector<FEN>& controle_lances, std::vector<std::vector<char>>& pecas_tabuleiro, int& turno);
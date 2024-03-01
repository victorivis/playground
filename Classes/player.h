#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <iostream>

struct trio{
	int r;
	int g;
	int b;
};

class Player{
    //Obrigatorio
    public:
        int HEIGHT;
        int WIDTH;
        enum Direcoes{
            Pausa=-1, Cima, Direita, Baixo, Esquerda
        };

    //Configuracoes
	public:
		int TAM_COBRA=10;
		int VEL=TAM_COBRA;
        int num_segmentos=1;
        short int direcao = -1;
        bool cobra_colorida=false;

        int cima, baixo, esquerda, direita;

        SDL_Rect cabeca = {500, 500, TAM_COBRA, TAM_COBRA};
        std::deque<SDL_Rect> segmentos_cobra;
        std::vector<trio> cores;
        std::vector<int> controles;

    public:
        public:
        Player(int w, int h, std::vector<int> z);
        void executar_controles(int tecla);
        void mover_cobra(int direcao);
        void colorir_cobra();
        void descolorir_cobra(trio cor_segmentos);
        void colisao_cobra(std::deque<SDL_Rect>& cobra_generica);
        void desenhar_cobra(SDL_Renderer** renderer);
        void atualizar_posicoes();
};
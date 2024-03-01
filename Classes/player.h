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
        trio cor_cobra;

        int cima, baixo, esquerda, direita;

        SDL_Rect cabeca = {500, 500, TAM_COBRA, TAM_COBRA};
        std::deque<SDL_Rect> segmentos_cobra;
        std::vector<trio> cores;
        std::vector<int> controles;

    public:
        public:
        Player(int w, int h, std::vector<int> z, trio cor_padrao={0, 0, 0});
        void executar_controles(int tecla);
        void mover_cobra(int direcao);
        void colorir_cobra();
        void descolorir_cobra();
        void colisao_cobra(std::deque<SDL_Rect>& cobra_generica);
        void desenhar_cobra(SDL_Renderer** renderer);
        void atualizar_posicoes();
};

class Maca{
    public:
        int WIDTH;
        int HEIGHT;
        int TAM_COBRA;
        int crescimento_maca=10;
        int max_maca;
        int macas_na_tela=max_maca;
        int minimo_sorteio=1;
        std::vector<SDL_Rect> macas;

    public:
        Maca(int w, int h, int tamanho_cobra, int num_max_macas=20, int minimo=1);
        void sortear_macas(bool primeiro_sorteio);
        void colisao_macas(Player& p);
        void desenhar_macas(SDL_Renderer** renderer, trio rgb);
};
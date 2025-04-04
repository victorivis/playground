#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <iostream>
#include <cstdio>

enum Operacao{
    Continuar, Sair
};

int rodar_menu_pausa(SDL_Renderer*& renderer, int width);
int rodar_menu_principal(SDL_Renderer*& renderer, int width);

class Menu{
    public:
        int width;
        int height;
        int NUMMENU;
        int retorno;
        TTF_Font* fonte;
        
        bool selecionado[10];
        std::vector<std::string> rotulo;
        std::vector<SDL_Surface*> molde;
        std::vector<SDL_Texture*> textura;
        std::vector<SDL_Color> cor;
        std::vector<SDL_Rect> posicao;

        SDL_Event evento_menu;        

    public:
        Menu(int width, int height);
        void inicializar(SDL_Renderer** renderer, std::vector<std::string>& nomes_para_rotulo, 
            std::string& caminho_fonte, int tamanho_fonte);
        int menu_generico(SDL_Renderer** renderer, std::vector<std::string> nomes_para_rotulo, 
            std::string caminho_fonte, int tamanho_fonte);
        void finalizar();
};
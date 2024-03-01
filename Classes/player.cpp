#include <SDL2/SDL.h>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "player.h"

Player::Player(int w, int h, std::vector<int> z){
            WIDTH = w;
            HEIGHT = h;
            controles=z;
        }

Player::void executar_controles(int tecla){
    switch(tecla){
       case controles[0]: if(direcao!=Baixo) direcao=Cima; break;
		case  controles[1]: if(direcao!=Cima) direcao=Baixo; break;
		case  controles[2]: if(direcao!=Esquerda) direcao=Direita; break;
		case  controles[3]:	if(direcao!=Direita) direcao=Esquerda; break;
    }
}
        
Player::void mover_cobra(int direcao){
    switch(direcao){
        case Cima: cabeca.y = (cabeca.y-VEL+HEIGHT)%HEIGHT; break;
        case Baixo: cabeca.y = (cabeca.y+VEL+HEIGHT)%HEIGHT; break;
        case Direita: cabeca.x = (cabeca.x+VEL+WIDTH)%WIDTH; break;
        case Esquerda: cabeca.x = (cabeca.x-VEL+WIDTH)%WIDTH; break;
    }
}

Player::void colorir_cobra(std::vector<trio>& cores){
    for_each(cores.begin(), cores.end(), [&](trio& cor){
        cor.r = rand()%256;
        cor.g = rand()%256;
        cor.b = rand()%256;
    });
}

Player::void descolorir_cobra(std::vector<trio>& cores, trio cor_segmentos={0, 0, 0}){
    for_each(cores.begin(), cores.end(), [&](trio& cor){
        cor.r = cor_segmentos.r;
        cor.g = cor_segmentos.g;
        cor.b = cor_segmentos.b;
    });
}

Player::void colisao_cobra(std::deque<SDL_Rect>& cobra_generica){
    for_each(cobra_generica.begin(), cobra_generica.end(), [&](auto& segmento){
        if(SDL_HasIntersection(&segmento, &cabeca)){
            num_segmentos = 1;
            //cout << "Colisao cabeca\n";
        }
    });
}
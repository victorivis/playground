#include "player.h"

Player::Player(int w, int h, std::vector<int> z){
    WIDTH = w;
    HEIGHT = h;
    controles=z;
}

void Player::executar_controles(int tecla){
    if(tecla == controles[0]){ if(direcao!=Baixo) direcao=Cima;}
	else if(tecla == controles[1]){ if(direcao!=Cima) direcao=Baixo;}
	else if(tecla == controles[2]){ if(direcao!=Esquerda) direcao=Direita;}
	else if(tecla == controles[3]){ if(direcao!=Direita) direcao=Esquerda;}
    else if(tecla == 'c'){printf("%d", cobra_colorida); cobra_colorida = !cobra_colorida; cobra_colorida ? colorir_cobra() : descolorir_cobra({0, 0, 0});}
}

void Player::mover_cobra(int direcao){
    switch(direcao){
        case Cima: cabeca.y = (cabeca.y-VEL+HEIGHT)%HEIGHT; break;
        case Baixo: cabeca.y = (cabeca.y+VEL+HEIGHT)%HEIGHT; break;
        case Direita: cabeca.x = (cabeca.x+VEL+WIDTH)%WIDTH; break;
        case Esquerda: cabeca.x = (cabeca.x-VEL+WIDTH)%WIDTH; break;
    }
}

void Player::colorir_cobra(){
    for_each(cores.begin(), cores.end(), [&](trio& cor){
        cor.r = rand()%256;
        cor.g = rand()%256;
        cor.b = rand()%256;
    });
}

void Player::descolorir_cobra(trio cor_segmentos={0, 0, 0}){
    for_each(cores.begin(), cores.end(), [&](trio& cor){
        cor.r = cor_segmentos.r;
        cor.g = cor_segmentos.g;
        cor.b = cor_segmentos.b;
    });
}

void Player::colisao_cobra(std::deque<SDL_Rect>& cobra_generica){
    for_each(cobra_generica.begin(), cobra_generica.end(), [&](SDL_Rect& segmento){
        if(SDL_HasIntersection(&segmento, &cabeca)){
            num_segmentos = 1;
            //cout << "Colisao cabeca\n";
        }
    });
}

void Player::desenhar_cobra(SDL_Renderer** renderer){
    for(int i=0; i<segmentos_cobra.size(); i++){
		SDL_SetRenderDrawColor(*renderer, cores[i].r, cores[i].g, cores[i].b, 255);
		SDL_RenderFillRect(*renderer, &(segmentos_cobra[i]));
	}
}

void Player::atualizar_posicoes(){
    segmentos_cobra.push_front(cabeca);

	while(segmentos_cobra.size() > num_segmentos){
		segmentos_cobra.pop_back();
	}

    while(cores.size() < segmentos_cobra.size()){
		if(cobra_colorida){
			cores.push_back({rand()%256, rand()%256, rand()%256});
		}
		else {
			cores.push_back({0, 0, 0});
		} 
	}

	while(cores.size() > segmentos_cobra.size()){
		cores.pop_back(); 
	}
}

/*
int main(){
    Player p1{1000, 600, {'w', 'a', 's', 'd'}};
    std::cout << "Hello World!\n";

    return 0;
}
*/
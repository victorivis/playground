#include "player.h"

Player::Player(int w, int h, std::vector<int> z, trio cor_padrao){
    WIDTH = w;
    HEIGHT = h;
    controles=z;
    cor_cobra = cor_padrao;
    cabeca.x = rand()%WIDTH;
    cabeca.y = rand()%HEIGHT;
}

void Player::executar_controles(int tecla){
    if(tecla == controles[0]){ if(num_segmentos==1 || direcao!=Baixo) direcao=Cima;}
	else if(tecla == controles[1]){ if(num_segmentos==1 || direcao!=Cima) direcao=Baixo;}
	else if(tecla == controles[2]){ if(num_segmentos==1 || direcao!=Esquerda) direcao=Direita;}
	else if(tecla == controles[3]){ if(num_segmentos==1 || direcao!=Direita) direcao=Esquerda;}
    else if(tecla == 'c'){printf("%d", cobra_colorida); cobra_colorida = !cobra_colorida; cobra_colorida ? colorir_cobra() : descolorir_cobra();}
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

void Player::descolorir_cobra(){
    for_each(cores.begin(), cores.end(), [&](trio& cor){
        cor.r = cor_cobra.r;
        cor.g = cor_cobra.g;
        cor.b = cor_cobra.b;
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
			cores.push_back(cor_cobra);
		} 
	}

	while(cores.size() > segmentos_cobra.size()){
		cores.pop_back(); 
	}
}

Maca::Maca(int w, int h, int tamanho_cobra, int num_max_macas, int minimo){
    WIDTH = w;
    HEIGHT = w;

    TAM_COBRA=tamanho_cobra;
    max_maca=num_max_macas;
    macas_na_tela=num_max_macas;
    minimo_sorteio = minimo;
    for(int i=0; i<num_max_macas; i++){
        macas.push_back({-10, -10, tamanho_cobra, tamanho_cobra});
    }
}

void Maca::sortear_macas(bool primeiro_sorteio=false){
    for_each(macas.begin(), macas.end(), [&](auto& rect_maca){
        if(rect_maca.x < 0 || primeiro_sorteio){
            rect_maca.x = rand()%(WIDTH/TAM_COBRA)*TAM_COBRA;
            rect_maca.y = rand()%(HEIGHT/TAM_COBRA)*TAM_COBRA;
            if(primeiro_sorteio){
                rect_maca.w = TAM_COBRA;
                rect_maca.h = TAM_COBRA;
            }
        }
    });
}

void Maca::colisao_macas(Player& p){
    for_each(macas.begin(), macas.end(), [&](auto& rect_maca){
		if(SDL_HasIntersection(&rect_maca, &p.cabeca)){
			p.num_segmentos+=crescimento_maca;
			macas_na_tela--;
			rect_maca.x = -10;
			rect_maca.y = -10;

            if(max_maca-macas_na_tela >= minimo_sorteio){
                sortear_macas(false);
                macas_na_tela = max_maca;
            }
		}
	});
}

void Maca::desenhar_macas(SDL_Renderer** renderer, trio rgb={255, 0, 0}){
    SDL_SetRenderDrawColor(*renderer, rgb.r, rgb.g, rgb.b, 255);
    for_each(macas.begin(), macas.end(), [&](auto& rect_maca){
		SDL_RenderFillRect(*renderer, &rect_maca);
	});
}

/*
int main(){
    Player p1{1000, 600, {'w', 'a', 's', 'd'}};
    std::cout << "Hello World!\n";

    return 0;
}
*/
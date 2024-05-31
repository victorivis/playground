#include "TextureManager.h"

SDL_Texture* loadTexture(SDL_Renderer* pRenderer, const char p_filePath[]){
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(pRenderer, p_filePath);

    if(texture == NULL){
        std::cout << "Falha ao carregar textura. Error: " << SDL_GetError() << "\n";
    }
    return texture;
}

void getTextureSize(SDL_Texture* textura, int& w, int& h){
    SDL_QueryTexture(textura, NULL, NULL, &w, &h);
}

void Imagem::render(){
    SDL_RenderCopy(renderer, textura_imagem, NULL, NULL);
}

Imagem::Imagem(SDL_Renderer* pRenderer, const char texture_sheet[])
:renderer(pRenderer){
    textura_imagem = loadTexture(pRenderer, texture_sheet);
}

Imagem::~Imagem(){
    SDL_DestroyTexture(textura_imagem);
    std::cout << "Textura da entidade excluida com sucesso\n";
}

Entity::Entity(SDL_Renderer* pRenderer, const char texture_sheet[], int posx, int posy)
:Imagem(pRenderer, texture_sheet){
    destRect.x = posx;
    destRect.y = posy;
    getTextureSize(textura_imagem, destRect.w, destRect.h);
}

void Entity::render(){
    SDL_RenderCopy(renderer, textura_imagem, NULL, &destRect);
}

//Player
Player::Player(SDL_Renderer* pRenderer, const char texture_sheet[], int posx, int posy, int speed)
:Entity(pRenderer, texture_sheet, posx, posy), player_speed(speed){
    last_move = STOP;
    controles = {'w', 's', 'a', 'd'};
}

void Player::executarControles(SDL_Keycode tecla){
    if(tecla == controles[0]){
        last_move = UP;
        destRect.y -= player_speed;
    }
    else if(tecla == controles[1]){
        last_move = DOWN;
        destRect.y += player_speed;
    }
    else if(tecla == controles[2]){
        last_move = LEFT;
        destRect.x -= player_speed;
    }
    else if(tecla == controles[3]){
        last_move = RIGHT;
        destRect.x += player_speed;
    }
    else{
        //std::cout<< "tecla pressionada " << (int) tecla << "\n"; 
    }
}
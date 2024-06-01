#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

SDL_Texture* loadTexture(SDL_Renderer* pRenderer, const char p_filePath[]);
void getTextureSize(SDL_Texture* textura, int& w, int& h);

enum Direcoes{
    STOP, UP, DOWN, LEFT, RIGHT
};

class Superficie{
    public:
        Superficie(const char p_filePath[]);
        ~Superficie();
        
        SDL_Surface* superficie_imagem;
};

class Imagem{
    public:
        Imagem(SDL_Renderer* pRenderer, const char p_filePath[]);
        ~Imagem();

        void render();

        SDL_Renderer* renderer;
        SDL_Texture* textura_imagem;
};

class Entity : public Imagem{
    public:
        Entity(SDL_Renderer* pRenderer, const char texture_sheet[], int posx, int posy);
        void render();

    public:
        SDL_Rect destRect;
};

class Player : public Entity{
    public:
        Player(SDL_Renderer* pRenderer, const char texture_sheet[], int posx, int posy, int speed);
        //void render();
        void executarControles(SDL_Keycode tecla);

    public:
        int player_speed;
        int last_move;
        std::vector<char> controles;
};
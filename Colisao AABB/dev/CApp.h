#ifndef CAPP_H
#define CAPP_H

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <array>
#include <iostream>
#include "TextureManager.h"
#include "Colisao.h"

class CApp{
    public:
        CApp();

        int OnExecute();
        bool OnInit();
        void OnEvent(SDL_Event *evento);
        void OnLoop();
        void OnRender();
        void OnExit();
        
    public:
        //std::vector<Entity> entidades;
        //std::vector<Player> player;
        bool isRunning;
        SDL_Window *pWindow;
        SDL_Renderer *pRenderer;
};

#endif
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
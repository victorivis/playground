#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>

void GetPixelRGB(SDL_Surface *surface, int posx, int posy, Uint8 *r, Uint8 *g, Uint8 *b);
char ColorToAscii(Uint8 r, Uint8 g, Uint8 b);
void MostrarPixelsImagem(const char caminho_imagem[]);
std::vector<std::string> PixelsImagemParaVetor(const char caminho_imagem[]);
void VetorParaArquivo(const std::vector<std::string>& vec, const std::string& filename);
//void StringVectorToFile(const std::vector<std::string>& vec, const std::string& filename);
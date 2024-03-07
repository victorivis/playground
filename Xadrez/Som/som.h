#pragma once
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

int loadMusic(const char* filename);
int loadSound(const char* filename);
void setVolume(int v);
int playMusic(int m);
int playSound(int s);
int initMixer();
void quitMixer();
void togglePlay();

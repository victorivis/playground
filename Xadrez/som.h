#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>

void generateSound(Uint8 *buffer, int length, int FREQUENCY);
void playSound(int FREQUENCY);

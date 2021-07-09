#pragma once
#include <SDL2/SDL_image.h>

void texInit(SDL_Renderer *rend);
SDL_Texture *texGet(int i);
void textFree();

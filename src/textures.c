#include "textures.h"

#define TEXTURES 2

static SDL_Texture* tex[32] = {0};

void texInit(SDL_Renderer *rend) {
    tex[0] = IMG_LoadTexture(rend, "res/boi.png");
    tex[1] = IMG_LoadTexture(rend, "res/boi2.png");
}

SDL_Texture* texGet(int i) {
    return tex[i];
}

void texFree() {
    for (int i=0; i<TEXTURES; i++)
        SDL_DestroyTexture(tex[i]);
}

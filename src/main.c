#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>

#include "loader.h"

#define WIDTH 800
#define HEIGHT 600

#define BG 200

#define SPD 5

static int camX = 0, camY = 0;

SDL_Window *win;
SDL_Renderer *rend;

SDL_Texture *boi1;
SDL_Texture *boi2;

object *world;
int worldSize;

struct {
    char w, a, s, d;
} keyboard;

enum Locs {
    X, Y
};

// initialization
void init() {
    // Window and renderer
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    win = SDL_CreateWindow(
        "jaq-the-cat/world",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        0);
    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    IMG_Init(IMG_INIT_PNG);

    boi1 = IMG_LoadTexture(rend, "res/boi.png");
    boi2 = IMG_LoadTexture(rend, "res/boi2.png");

    world = loadWorld("res/world.json", &worldSize);
}

SDL_Texture* getTexture(const char *name) {
    if (!strcmp(name, "boi"))
        return boi1;
    else if (!strcmp(name, "boi2"))
        return boi2;
    return NULL;
}

void end() {
    free(world);

    SDL_DestroyTexture(boi1);
    SDL_DestroyTexture(boi2);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
}

// rendering
void render() {
    SDL_Rect display;

    for (int i=0; i<worldSize; i++) {
        // set display rectangle to object's (x, y) and a fixed width and height
        display.x = world[i].x - camX;
        display.y = world[i].y - camY;
        display.w = 25;
        display.h = 25;

        if (display.x+display.w >= 0 && display.x <= WIDTH &&
        display.y+display.h >= 0 && display.y <= HEIGHT) { // if object is actually inside the screen
            SDL_RenderCopy(rend, getTexture(world[i].texture), NULL, &display);
        }
    }
}

// processing
int handleev() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_Q:
            return 1;
        case SDL_SCANCODE_W:
            keyboard.w = event.key.type == SDL_KEYDOWN;
            break;
        case SDL_SCANCODE_A:
            keyboard.a = event.key.type == SDL_KEYDOWN;
            break;
        case SDL_SCANCODE_S:
            keyboard.s = event.key.type == SDL_KEYDOWN;
            break;
        case SDL_SCANCODE_D:
            keyboard.d = event.key.type == SDL_KEYDOWN;
            break;
        default:
            break;
    }
    return 0;
}

void update() {
    if (keyboard.w)
        camY -= SPD;
    if (keyboard.s)
        camY += SPD;

    if (keyboard.a)
        camX -= SPD;
    if (keyboard.d)
        camX += SPD;
}

int main() {
    init();

    int close = 0;
    while (!close) {
        close = handleev();
        update();
        SDL_SetRenderDrawColor(rend, BG, BG, BG, 255);
        SDL_RenderClear(rend);
        render();
        SDL_RenderPresent(rend);
    }

    end();

    return 0;
}

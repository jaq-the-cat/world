#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 800
#define HEIGHT 600
#define WWIDTH 2000
#define WHEIGHT 2000

#define BG 200

#define SPD 20

static int camX = 0, camY = 0;

SDL_Window *win;
SDL_Renderer *rend;

SDL_Texture *boi;

struct {
    char w, a, s, d;
} keyboard;

// world (get from res/world.json later)
enum Locs {
    X, Y
};

int world[][2] = {
    {0, 0},
    {50, 50},
    {100, 100},
    {0, 200},
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

    boi = IMG_LoadTexture(rend, "res/boi.png");
}

// rendering
void render() {
    SDL_Rect display;
    for (int i=0; i<4; i++) {
        display.x = world[i][X] - camX;
        display.y = world[i][Y] - camY;
        display.w = 40;
        display.h = 40;
        SDL_RenderCopy(rend, boi, NULL, &display);
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
        camY += SPD;
    if (keyboard.s)
        camY -= SPD;

    if (keyboard.a)
        camX += SPD;
    if (keyboard.d)
        camX -= SPD;
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

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    return 0;
}

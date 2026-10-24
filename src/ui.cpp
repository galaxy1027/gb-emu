#include "ui.h"
#include <SDL_events.h>

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
SDL_Surface *screen;

SDL_Window *debug_window;
SDL_Renderer *debug_renderer;
SDL_Texture *debug_texture;
SDL_Surface *debug_screen;

void UI::init() {
    int debugW = (16 * 8) * scale;
    int debugH = (24 * 8) * scale;
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_CreateWindowAndRenderer(debugW, debugH, SDL_RENDERER_PRESENTVSYNC,
                                &debug_window, &debug_renderer);

    debug_screen = SDL_CreateRGBSurface(0, debugW, debugH, 32, 0x00FF0000,
                                        0x0000FF00, 0x000000FF, 0xFF000000);

    debug_texture =
        SDL_CreateTexture(debug_renderer, SDL_PIXELFORMAT_ARGB8888,
                          SDL_TEXTUREACCESS_STREAMING, debugW, debugH);
}

void UI::clean() { SDL_DestroyWindow(debug_window); }

void UI::updateDebugWindow() {
    int tileNum = 0;
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = debug_screen->w;
    rect.h = debug_screen->h;
    SDL_FillRect(debug_screen, &rect, 0xFF111111);
    uint16_t addr = 0x8000;

    for (int y = 0; y < 24; y++) {
        for (int x = 0; x < 16; x++) {
            displayTile(debug_screen, addr, tileNum, x * 8 * scale,
                        y * 8 * scale);
            tileNum++;
        }
    }
    SDL_UpdateTexture(debug_texture, NULL, debug_screen->pixels,
                      debug_screen->pitch);
    SDL_RenderClear(debug_renderer);
    SDL_RenderCopy(debug_renderer, debug_texture, NULL, NULL);
    SDL_RenderPresent(debug_renderer);
}

void UI::update() {
    SDL_Event event;
    updateDebugWindow();
    SDL_PollEvent(&event);
    switch (event.type) {
    case SDL_QUIT:
        running = false;
        break;
    }
}

void UI::displayTile(SDL_Surface *surface, uint16_t startLocation,
                     uint16_t tileNum, int x, int y) {
    SDL_Rect rect;

    for (int row = 0; row < 8; row++) {
        uint16_t addr = startLocation + tileNum * 16 + row * 2;
        uint8_t lo = bus.read(addr);
        uint8_t hi = bus.read(addr + 1);

        for (int col = 0; col < 8; col++) {
            int bit = 7 - col;

            uint8_t color = (((hi >> bit) & 1) << 1) | ((lo >> bit) & 1);

            rect = {x + col * scale, y + row * scale, scale, scale};
            SDL_FillRect(surface, &rect, tile_colors[color]);
        }
    }
}
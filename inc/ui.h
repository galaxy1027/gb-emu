#pragma once

#include "bus.h"
#include <SDL2/SDL.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_video.h>

#define SCREEN_WIDTH (160 * scale)
#define SCREEN_HEIGHT (144 * scale)

class UI {
  public:
    bool running = true;
    int scale = 2;
    int debugW;
    int debugH;

    const uint32_t tile_colors[4] = {0xFFE0F8D0, 0xFF86C06C, 0xFF306850,
                                     0xFF071821};
    Bus &bus;
    UI(Bus &b, int scale) : bus(b) {
        this->scale = scale;
        init();
    };

    void init();
    void clean();
    void updateDebugWindow();
    void update();

    void displayTile(SDL_Surface *surface, uint16_t startLocation,
                     uint16_t tileNum, int x, int y);
};

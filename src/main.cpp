#include "cpu.h"
#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <iostream>
#include <memory>

#define debug false

int initWindow();

SDL_Window *gbWindow;
SDL_Renderer *gbRenderer;

void debugLoop(Cpu &cpu) {
    bool running = false;
    initWindow();
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_RETURN:
                    cpu.step();
                    cpu.printRegs();
                    break;
                }
            }
        }
        SDL_RenderPresent(gbRenderer);
    }
}

void mainLoop(Cpu &cpu) {
    bool running = true;
    while (running) {
        cpu.step();
    }
}

int initWindow() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL INIT FAILED\n" << SDL_GetError() << "\n";
        return 1;
    }
    uint32_t sdlWindowFlags = SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN |
                              SDL_WINDOW_RESIZABLE | SDL_WINDOW_MINIMIZED |
                              SDL_WINDOW_INPUT_FOCUS;

    gbWindow =
        SDL_CreateWindow("Gameboy Emulator", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 1000, 1000, sdlWindowFlags);
    if (gbWindow == NULL) {
        std::cout << "SDL CREATE WINDOW FAILED\n" << SDL_GetError() << "\n";
        return 1;
    }

    gbRenderer = SDL_CreateRenderer(gbWindow, -1, 0);

    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./gb-emu <path-to-ROM>\n";
        return 1;
    }

    auto cpu = std::make_unique<Cpu>();

    if (cpu->loadRom(std::string(argv[1])) == 1) {
        return 1;
    }

    if (debug) {
        debugLoop(*cpu);
    } else {
        mainLoop(*cpu);
    }

    return 0;
}

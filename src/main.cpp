#include "bus.h"
#include "cpu.h"
#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <iostream>

#define running true

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./gb-emu <path-to-ROM>\n";
        return 1;
    }

    Bus bus = Bus();
    Cpu cpu = Cpu(bus);
    if (bus.loadRom(argv[1]) != 0)
        return 1;

    while (running) {
        int cycles = cpu.step();
        bus.tick(cycles);
    }

    return 0;
}

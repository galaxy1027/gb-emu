#include "bus.h"
#include "cpu.h"
#include "ui.h"

#include <SDL_video.h>
#include <iostream>

#define CYCLES_PER_FRAME 70224

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./gb-emu <path-to-ROM> <optional: scale>\n";
        return 1;
    }

    int scale = 1;
    if (argc == 3) {
        scale = atoi(argv[2]);
    }

    Bus bus = Bus();
    Cpu cpu = Cpu(bus);
    UI ui = UI(bus, scale);

    if (bus.loadRom(argv[1]) != 0)
        return 1;

    while (ui.running) {
        int frame_cycles = 0;
        while (frame_cycles < CYCLES_PER_FRAME && ui.running) {
            int cycles = cpu.step();
            bus.tick(cycles);
            frame_cycles += cycles;
        }
        ui.update();
    }
    ui.clean();
    SDL_Quit();
    return 0;
}

#include "cpu.h"
#include <iostream>
#include <memory>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./gb-emu <path-to-ROM>\n";
        return 1;
    }

    auto cpu = std::make_unique<Cpu>();
    if (cpu->loadRom(std::string(argv[1])) == 1) {
        return 1;
    }
    while (true) {
        cpu->cycle();
    }

    return 0;
}

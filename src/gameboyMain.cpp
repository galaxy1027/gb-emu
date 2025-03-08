#include <iostream>
#include "gb.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Error: please provide 2 arguments\n"
            << "./gameboyMain <path-to-rom>\n";
        return 1;
    }
    GameBoy *emu = new GameBoy();
    emu->LoadRom(argv[1]);
    uint8_t opcode;
    for (int i = 0; i <= 1; i++) {
        opcode = emu->Fetch();
        std::cout << std::hex << (unsigned int)opcode << '\n';
        emu->Execute(opcode);
    }
    delete(emu);
    return 0;
}

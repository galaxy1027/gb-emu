#include <iostream>
#include "gb.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cout << "Wrong number of args (need 2)\n";
        return 1;
    }
    std::cout << "--Register Tests--\n";

    GameBoy *emu = new GameBoy();
    emu->LoadRom(argv[1]);
    emu->WriteRegister(AF, 0x1234);
    emu->WriteRegister(BC, 0x5678);
    emu->WriteRegister(DE, 0x90AB);
    emu->WriteRegister(HL, 0xCDEF);
    emu->PrintRegisters();


    std::cout << "-- Preview of ROM contents -- \n";

    emu->PrintMemory(cartridge_base_addr, 100);


    return 0;
}

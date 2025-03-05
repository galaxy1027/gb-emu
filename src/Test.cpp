#include <iostream>
#include "gb.hpp"

int main(int argc, char **argv)
{
    std::cout << "--Register Tests--\n";

    GameBoy *emu = new GameBoy();
    emu->WriteRegister(AF, 0x1234);
    emu->WriteRegister(BC, 0x5678);
    emu->WriteRegister(DE, 0x90AB);
    emu->WriteRegister(HL, 0xCDEF);

    emu->PrintRegisters();
}

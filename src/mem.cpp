#include <iostream>
#include <cstdio>
#include "types.h"
#include "mem.hpp"

byte Memory::ReadWram(uint16_t address) {
    return this->WRAMBase[address];
}

byte Memory::ReadVram(uint16_t address) {
    return this->VRAMBase[address];
}

int Memory::LoadRom(std::string romPath) {
    FILE *ROM = std::fopen(romPath.c_str(), "r");
    if (ROM == NULL)
    {
        std::cerr << "Error opening rom, make sure the file exists!\n";
        return 1;
    }

    std::fseek(ROM, 0, SEEK_END);
    int filesize = std::ftell(ROM);
    rewind(ROM);

    if (filesize > MAX_ROM_SIZE)
    {
        std::cerr << "ROM is too big!\n";
        return -1;
    }

    std::fread(CartridgeBase, sizeof(byte), filesize, ROM);
    return 0;
}

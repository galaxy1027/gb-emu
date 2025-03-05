#include <cstdio>
#include <iostream>
#include "types.h"
#include "memory.hpp"

byte Memory::ReadByte(uint16_t address) {
    return this->memoryMap[address];
}

void Memory::WriteByte(uint16_t address, byte value) {
    this->memoryMap[address] = value;
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

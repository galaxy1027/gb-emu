#ifndef MEM_H
#define MEM_H

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include "types.h"

#define MAX_ROM_SIZE (32 * 1024)

class Memory
{
private:
    byte memoryMap[64 * 1024]; // 64KB memory map

    // Pointers to base addresses of each memory region
    byte* CartridgeBase = memoryMap + 0x0000;
    byte* VRAMBase = memoryMap + 0x8000;
    byte* WRAMBase = memoryMap + 0xC000;

public:
    byte ReadWram(uint16_t address)
    {
        return WRAMBase[address];
    }

    byte ReadVram(uint16_t address)
    {
        return VRAMBase[address];
    }

    /*
        Load Rom
        Parameter: string containing relative file path to ROM file to be read.
        Stores this rom in working memory. Rom file must be in binary format.
        Error codes:
        1 = file was not opened, does not exist
        -1 = file is too big
    */
    int LoadRom(std::string romPath)
    {
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
};

#endif

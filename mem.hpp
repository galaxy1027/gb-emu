#ifndef MEM_H
#define MEM_H

#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include "types.h"

class Memory
{
private:
    // Contains 8mb of working memory and 8mb of video memory
    byte Wram[8 * 1024];
    byte Vram[8 * 1024];

public:
    byte ReadWram(uint16_t address)
    {
        return Wram[address];
    }

    byte ReadVram(uint16_t address)
    {
        return Vram[address];
    }

    int LoadRom(std::string filePath)
    {
        std::ifstream file(filePath, std::ios::binary);

        if (!file.is_open())
        {
            std::cerr << "Error opening ROM file!\n";
            return 1;
        }

        // Get file size
    }
};

#endif
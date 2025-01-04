#ifndef MEM_H
#define MEM_H

#include <cstdint>
#include <string>
#include "types.h"

class Memory
{
private:
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

    void ReadFile(std::string filePath)
    {
    }
};

#endif
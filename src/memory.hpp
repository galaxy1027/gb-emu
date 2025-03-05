#ifndef MEM_H
#define MEM_H

#include <cstdint>
#include <string>
#include "types.h"

#define MAX_ROM_SIZE (32 * 1024)

class Memory {
private:
    byte memoryMap[64 * 1024]; // 64KB memory map

    // Pointers to base addresses of each memory region
    byte* CartridgeBase = memoryMap + 0x0000;
    byte* VRAMBase = memoryMap + 0x8000;
    byte* WRAMBase = memoryMap + 0xC000;

public:
    byte ReadByte(uint16_t address);
    void WriteByte(uint16_t address, byte value);
    /*
        Load Rom
        Parameter: string containing relative file path to ROM file to be read.
        Stores this rom in working memory. Rom file must be in binary format.
        Error codes:
        1 = file was not opened, does not exist
        -1 = file is too big
    */
    int LoadRom(std::string romPath);
};

#endif

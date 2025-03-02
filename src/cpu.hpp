#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <iostream>
#include "mem.hpp"

class CPU
{
public:
    uint16_t AF;
    uint16_t BC;
    uint16_t DE;
    uint16_t HL;
    Memory *mem;

private:
    uint16_t PC;
    uint16_t SP;
    byte opcode;

public:
    CPU()
    {
        AF = 0;
        BC = 0;
        DE = 0;
        HL = 0;
        mem = new Memory();
    }

    ~CPU()
    {
        delete mem;
    }

    void PrintRegisters()
    {
        std::cout << "-- Registers --\n"
                  << "AF: " << AF << '\n'
                  << "BC: " << BC << '\n'
                  << "DE: " << DE << '\n'
                  << "HL: " << HL << '\n';
    }

    void fetch()
    {
        opcode = mem->ReadWram(PC);
    }

    void execute()
    {
        switch (opcode)
        {
        case 0x00: // NOP
            break;
        default:
            std::cout << "Error: Undefined opcode\n";
        }
    }
};

#endif

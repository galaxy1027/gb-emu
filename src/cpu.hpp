#ifndef CPU_H
#define CPU_H

#include "types.h"

class CPU {
public:
    uint16_t AF;
    uint16_t BC;
    uint16_t DE;
    uint16_t HL;
    uint16_t PC;
    uint16_t SP;
private:
    byte opcode;

public:
    CPU();
};

#endif

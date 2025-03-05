#ifndef CPU_H
#define CPU_H

#include "types.h"

class CPU {
public:
    reg AF;
    reg BC;
    reg DE;
    reg HL;
    reg PC;
    reg SP;
private:
    byte opcode;

public:
    CPU();
};

#endif

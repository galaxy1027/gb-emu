#include <iostream>
#include "cpu.hpp"
#include "mem.hpp"

int main(int argc, char **argv)
{
    std::cout << "--Register Tests--\n";

    CPU *cpu = new CPU();
    cpu->AF = 0x1234;
    cpu->BC = 0x5678;
    cpu->DE = 0x90AB;
    cpu->HL = 0xCDEF;
    cpu->PrintRegisters();
}
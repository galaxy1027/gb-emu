#include <iostream>
#include "cpu.hpp"

CPU::CPU() {
    this->AF = 0;
    this->BC = 0;
    this->DE = 0;
    this->HL = 0;
}

void CPU::PrintRegisters() {
    std::cout << "-- Registers --\n"
    << "AF: " << AF << '\n'
    << "BC: " << BC << '\n'
    << "DE: " << DE << '\n'
    << "HL: " << HL << '\n';
}

void CPU::Fetch() {
    opcode = mem.ReadWram(this->PC);
}

void CPU::Execute() {
    switch (opcode) {
        case 0x00:
            break;
        default:
            std::cout << "Error: Undefined opcode\n";
    }
}

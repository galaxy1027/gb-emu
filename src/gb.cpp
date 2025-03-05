#include <iostream>
#include "gb.hpp"
#include "cpu.hpp"
#include "memory.hpp"

GameBoy::GameBoy() {
    this->cpu = new CPU();
    this->memory_map = new Memory();
}

/*
    Fetch
    Reads a byte from the program counter (PC)'s location and stores it.
    Also increments the PC once completed.
*/
void GameBoy::Fetch() {
    this->opcode = memory_map->ReadByte(cpu->PC);
    cpu->PC++;
}

/*
    Execute
*/
void GameBoy::Execute() {
    switch (this->opcode) {
        case 0x00:
            break;
        default:
            std::cerr << "Error: OpCode not implemented yet\n";
            break;
    }
}


void GameBoy::WriteRegister(register_select_t registerName, uint16_t value) {
    switch (registerName) {
        case AF:
            this->cpu->AF = value;
            break;
        case BC:
            this->cpu->BC = value;
            break;
        case DE:
            this->cpu->DE = value;
            break;
        case HL:
            this->cpu->HL = value;
            break;
        defualt:
            std::cerr << "Error: Register does not exist\n";
    }
}

void GameBoy::PrintRegisters() {
    std::cout << "-- Registers --\n"
    << "AF: 0x" << std::hex << std::uppercase << cpu->AF << '\n'
    << "BC: 0x" << std::hex << std::uppercase << cpu->BC << '\n'
    << "DE: 0x" << std::hex << std::uppercase << cpu->DE << '\n'
    << "HL: 0x" << std::hex << std::uppercase << cpu->HL << '\n';
}

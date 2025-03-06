#include <iostream>
#include <iomanip>
#include <string>
#include "gb.hpp"
#include "cpu.hpp"
#include "memory.hpp"

GameBoy::GameBoy() {
    this->cpu = new CPU();
    this->memory_map = new Memory();
}

int GameBoy::LoadRom(std::string path) {
    return this->memory_map->LoadRom(path);
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
    << "AF: 0x" << std::hex << cpu->AF << '\n'
    << "BC: 0x" << std::hex << cpu->BC << '\n'
    << "DE: 0x" << std::hex << cpu->DE << '\n'
    << "HL: 0x" << std::hex << cpu->HL << '\n';
}

void GameBoy::PrintMemory(uint16_t start_address, unsigned int bytes) {
    std::uint8_t out = 0;
    for (int i = 0; i < bytes; i++) {
        out = this->memory_map->ReadByte(start_address + i);
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (unsigned int)out << ' ';
    }
}

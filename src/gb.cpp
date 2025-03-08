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

GameBoy::~GameBoy() {
    delete this->cpu;
    delete this->memory_map;
}

int GameBoy::LoadRom(std::string path) {
    return this->memory_map->LoadRom(path);
}
/*
    Fetch
    Reads a byte from the program counter (PC)'s location and stores it.
    Also increments the PC once completed.
*/
byte GameBoy::Fetch() {
    byte out = memory_map->ReadByte(cpu->PC);
    cpu->PC++;
    return out;
}

/*
    Execute
*/
void GameBoy::Execute(byte opcode) {
    switch (opcode) {
        case 0x00: // NOP
            break;
        case 0x31: { // LD SP, u16
            byte lower = Fetch();
            byte upper = Fetch();
            cpu->SP = ((uint16_t)lower) | ((uint16_t)upper << 8);
            std::cout <<"Stack Pointer:"<< std::hex << cpu->SP << '\n';
            break;
        }
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
        default:
            std::cerr << "Error: Register does not exist\n";
    }
}

void GameBoy::PrintRegisters() {
    std::cout << "-- Registers --\n"
    << "AF: 0x" << std::hex << std::setfill('0') << std::setw(4) << cpu->AF << '\n'
    << "BC: 0x" << std::hex << std::setfill('0') << std::setw(4) << cpu->BC << '\n'
    << "DE: 0x" << std::hex << std::setfill('0') << std::setw(4) << cpu->DE << '\n'
    << "HL: 0x" << std::hex << std::setfill('0') << std::setw(4) << cpu->HL << '\n'
    << "SP: 0x" << std::hex << std::setfill('0') << std::setw(4) << cpu->SP << '\n'
    << "PC: 0x" << std::hex << std::setfill('0') << std::setw(4) << cpu->PC << '\n';
}

void GameBoy::PrintMemory(uint16_t start_address, unsigned int bytes) {
    std::uint8_t out = 0;
    for (int i = 0; i < bytes; i++) {
        out = this->memory_map->ReadByte(start_address + i);
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (unsigned int)out << ' ';
    }
}

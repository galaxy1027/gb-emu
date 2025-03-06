#ifndef GAMEBOY_H
#define GAMEBOY_H
#include <string>
#include "cpu.hpp"
#include "memory.hpp"

typedef enum {AF, BC, DE, HL} register_select_t;

class GameBoy {
private:
    CPU *cpu;
    Memory *memory_map;
    byte opcode;
public:
    GameBoy();
    int LoadRom(std::string path);
    void Fetch();
    void Execute();
    void WriteRegister(register_select_t registerName, uint16_t value);
    void PrintRegisters();
    void PrintMemory(uint16_t address, unsigned int bytes);
    };


#endif

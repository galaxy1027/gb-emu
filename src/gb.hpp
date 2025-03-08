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
public:
    GameBoy();
    ~GameBoy();
    int LoadRom(std::string path);
    byte Fetch();
    void Execute(byte opcode);
    void WriteRegister(register_select_t registerName, uint16_t value);
    void PrintRegisters();
    void PrintMemory(uint16_t address, unsigned int bytes);
    };


#endif

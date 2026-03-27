#include "cpu.h"
#include "opcode.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

Cpu::Cpu() {
    memory.fill(0);
    PC.val = 0x1000;
    initOpcodeTable();
    AF.val = (0x01B0);
    BC.val = (0x0013);
    DE.val = (0x00D8);
    HL.val = (0x014D);

    SP.val = (0xFFFE);
    PC.val = (0x0100);
}

int Cpu::loadRom(const std::filesystem::path &path) {
    int loaded = 0;
    std::filesystem::path filePath = path;
    std::ifstream file(filePath, std::ios::binary);
    if (!file || filePath.extension() != ".gb") {
        std::cerr << "Error: Attempted to load invalid ROM!\n";
        loaded = 1;
    } else {
        std::vector<uint8_t> rom((std::istreambuf_iterator<char>(file)),
                                 std::istreambuf_iterator<char>());

        for (size_t i = 0; i < rom.size() && i < 0x8000; i++) {
            memory[i] = rom[i];
        }
        std::cout << "Rom Loaded\n";
    }
    file.close();
    return loaded;
}

uint8_t Cpu::fetch() { return memory[PC.val++]; }

uint16_t Cpu::fetch16() {
    uint8_t lo = fetch();
    uint8_t hi = fetch();
    return ((uint16_t)hi << 8) | lo;
}
void Cpu::execute(uint8_t opcode_fetched) {
    const struct opcode *op = &opcodeTable[opcode_fetched];
    if (op->handler) {
        (this->*op->handler)(opcode_fetched);
        // std::cout << "Opcode 0x" << std::hex << (int)opcode_fetched << "\n";
    } else
        std::cout << "Unimplemented opcode 0x" << std::hex
                  << (int)opcode_fetched << "\n";
    t_cycles = op->t_states;
}

void Cpu::cycle() {
    if (t_cycles == 0 && !stopped) {
        uint8_t opcode = fetch();
        execute(opcode);

        if (IME_Pending) {
            IME = IME_Pending;
            IME_Pending = false;
        }

    } else {
        t_cycles--;
    }
}

/***********************************************************
 * Private Helper Functions
 **********************************************************/

void Cpu::writeByteMemory(uint16_t address, uint8_t data) {
    memory[address] = data;

    if (address == 0xFF02) { // Serial port is being written to
        if (data & 0x80) {   // Transfer start signal
            uint8_t ch = memory[0xFF01];
            std::cout << (char)ch;
            // Complete transfer
            memory[0xFF01] = 0xFF;
            memory[0xFF02] &= ~0x80;
        }
    }
}
uint8_t Cpu::readByteMemory(uint16_t addr) { return memory[addr]; }

uint8_t *Cpu::getMemoryPtr(uint16_t addr) { return &memory[addr]; }

void Cpu::store8(uint8_t data, uint16_t address) {
    writeByteMemory(address, data);
}
void Cpu::store16(uint16_t data, uint16_t address) {
    uint8_t lo = data & 0x00FF;
    uint8_t hi = (data & 0xFF00) >> 8;
    writeByteMemory(address, lo);
    writeByteMemory(address + 1, hi);
}

uint8_t Cpu::read8(uint16_t addr) { return readByteMemory(addr); }
uint16_t Cpu::read16(uint16_t addr) {
    return ((uint16_t)readByteMemory(addr + 1) << 8) |
           (uint16_t)readByteMemory(addr);
}

/*
 * Read / Write Flag
 * Perform a bit shift to read from or write to a specific bit in the Flags (F)
 * register. The bit numbers are specified in the Flag enum class.
 */

bool Cpu::readFlag(Flag F) { return (AF.lo >> static_cast<int>(F)) & 1; }

void Cpu::writeFlag(Flag F, bool value) {
    if (value) {
        AF.lo |= 1 << static_cast<int>(F);
    } else {
        AF.lo &= ~(1 << static_cast<int>(F));
    }
    AF.lo &= 0xF0;
}
void Cpu::load8(uint16_t addr, uint8_t &dest) { dest = read8(addr); }
void Cpu::loadReg16(uint16_t addr, Reg16 &dest) { dest.val = read16(addr); }

void Cpu::incReg16(Reg16 &reg) { reg.val++; }
void Cpu::decReg16(Reg16 &reg) { reg.val--; }

void Cpu::addReg16(uint16_t &dest, uint16_t &source) {
    uint32_t sum = source + dest;
    add16SetH(source, dest);
    writeFlag(Flag::N, 0);
    writeFlag(Flag::C, (sum > 0xFFFF));
    dest = sum & 0x0000FFFF;
}

/*
 * Addition / subtraction set H
 * Helpers to set H according to the result of an addition or subtraction
 * operation
 */
void Cpu::addSetH(uint8_t a, uint8_t b) {
    bool halfCarry = (a & 0x0F) + (b & 0x0F) > 0x0F;
    writeFlag(Flag::H, halfCarry);
}

void Cpu::add16SetH(uint16_t a, uint16_t b) {
    bool halfCarry = (a & 0x0FFF) + (b & 0x0FFF) > 0x0FFF;
    writeFlag(Flag::H, halfCarry);
}

void Cpu::subSetH(uint8_t a, uint8_t b) {
    bool halfCarry = (a & 0x0F) < (b & 0x0F);
    writeFlag(Flag::H, halfCarry);
}

/*
 * RLCX
 * Takes a register and shifts it left.
 * The 7th bit is shifted out and rotated to bit 0.
 * It is also saved to flag C.
 */
void Cpu::rotateLeftCarry(uint8_t &reg) {
    uint8_t oldBit7 = reg & 0x80;
    reg = (reg << 1) | (oldBit7 >> 7);
    writeFlag(Flag::Z, 0);
    writeFlag(Flag::N, 0);
    writeFlag(Flag::H, 0);
    writeFlag(Flag::C, oldBit7 != 0);
}

/*
 * RRCX
 * Works the same as RCLX, but shifts right
 */
void Cpu::rotateRightCarry(uint8_t &reg) {
    uint8_t oldBit0 = reg & 0x01;
    reg = (reg >> 1) | (oldBit0 << 7);
    writeFlag(Flag::Z, 0);
    writeFlag(Flag::N, 0);
    writeFlag(Flag::H, 0);
    writeFlag(Flag::C, oldBit0 != 0);
}

void Cpu::rotateLeft(uint8_t &reg) {
    bool oldCarry = readFlag(Flag::C);
    writeFlag(Flag::C, (reg & 0x80) >> 7);
    reg = (reg << 1) | (static_cast<uint8_t>(oldCarry));
}
void Cpu::rotateRight(uint8_t &reg) {
    bool oldCarry = readFlag(Flag::C);
    writeFlag(Flag::C, (reg & 0x01));
    reg = (reg >> 1) | (static_cast<uint8_t>(oldCarry) << 7);
}

/*
 * Perform an arithmetic left shift on register, filling in bit 0 with 0.
 */
void Cpu::shiftLeftArithmetic(uint8_t &reg) {
    writeFlag(Flag::C, (reg >> 7) & 0x01);
    reg = reg << 1;
    reg &= 0xFE;
    writeFlag(Flag::N, 0);
    writeFlag(Flag::H, 0);
    writeFlag(Flag::Z, reg == 0);
}
/*
 * Perform an arithmetic right shift on register, filling in bit 7 with the
 * previous value.
 */
void Cpu::shiftRightArithmetic(uint8_t &reg) {
    uint8_t oldBit7 = reg & 0x7F;
    writeFlag(Flag::C, reg & 0x01);
    reg = reg >> 1;
    reg |= oldBit7;
    writeFlag(Flag::N, 0);
    writeFlag(Flag::H, 0);
    writeFlag(Flag::Z, reg == 0);
}
void Cpu::shiftRightLogical(uint8_t &reg) {
    writeFlag(Flag::C, reg & 0x01);
    reg = reg >> 1;
    reg &= 0xEF;
    writeFlag(Flag::N, 0);
    writeFlag(Flag::H, 0);
    writeFlag(Flag::Z, reg == 0);
}

void Cpu::swapNibbles(uint8_t &reg) {
    uint8_t temp = reg;
    reg = 0 | ((reg & 0x0F) << 4) | ((reg & 0xF0) >> 4);
    writeFlag(Flag::Z, reg == 0);
    writeFlag(Flag::N, 0);
    writeFlag(Flag::H, 0);
    writeFlag(Flag::C, 0);
}

void Cpu::copyBit(uint8_t &reg, int bitPos) {
    writeFlag(Flag::Z, (reg & (1 << bitPos)) == 0);
    writeFlag(Flag::N, 0);
    writeFlag(Flag::H, 1);
}

void Cpu::resetBit(uint8_t &reg, int bitPos) { reg &= ~(1 << bitPos); }
void Cpu::setBit(uint8_t &reg, int bitPos) { reg |= 1 << bitPos; }

uint8_t Cpu::pop() {
    uint8_t popped = readByteMemory(SP.val);
    SP.val++;
    return popped;
}
uint16_t Cpu::pop16() {
    uint16_t popped = readByteMemory(SP.val);
    SP.val++;
    popped |= readByteMemory(SP.val) << 8;
    SP.val++;
    return popped;
}
void Cpu::push(uint8_t data) {
    SP.val--;
    writeByteMemory(SP.val, data);
}
void Cpu::push16(uint16_t data) {
    push((data >> 8) & 0x00FF);
    push(data & 0x00FF);
}

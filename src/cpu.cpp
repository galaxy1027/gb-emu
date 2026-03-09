#include "cpu.h"
#include "opcode.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

Cpu::Cpu() {
  memory.fill(0);
  PC = 0x0100;
  initOpcodeTable(opcodeTable);
  AF.loadReg(0x01B0);
  BC.loadReg(0x0013);
  DE.loadReg(0x00D8);
  HL.loadReg(0x014D);

  SP = 0xFFFE;
  PC = 0x0100;
}

int Cpu::loadRom(const std::string &path) {
  int loaded = 0;
  std::ifstream file(path, std::ios::binary);

  if (!file) {
    std::cerr << "Error: Attempted to load invalid ROM!\n";
    loaded = 1;
  } else {
    std::vector<uint8_t> rom((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());

    for (size_t i = 0; i < rom.size() && i < 0x8000; i++) {
      memory[i] = rom[i];
    }
  }
  std::cout << "Rom Loaded\n";
  return loaded;
}

uint8_t Cpu::fetch() { return memory[PC++]; }

uint16_t Cpu::fetch16() {
  uint8_t lo = fetch();
  uint8_t hi = fetch();
  return ((uint16_t)hi << 8) | lo;
}

void Cpu::op_0x00() {} // NOP
void Cpu::op_0x01() {  // LD BC, d16
  uint16_t d16 = fetch16();
  BC.loadReg(d16);
}
void Cpu::op_0x02() { // LD (BC), A
  uint16_t addr = BC.GetVal();
  store8(AF.hi, addr);
}
void Cpu::op_0x03() { // INC BC
  uint16_t data = BC.GetVal();
  BC.loadReg(data + 1);
}
void Cpu::op_0x04() { // INC B
  incReg(BC.hi);
}
void Cpu::op_0x05() { // DEC B
  decReg(BC.hi);
}
void Cpu::op_0x06() { // LD B, d8
  uint8_t d8 = fetch();
  BC.hi = d8;
}
void Cpu::op_0x07() { // RLCA
  RLCX(AF.hi);
}
void Cpu::op_0x08() { // LD (a16), SP
  uint16_t a16 = fetch16();
  store16(SP, a16);
}

void Cpu::execute(uint8_t opcode_fetched) {
  const struct opcode *op = &opcodeTable[opcode_fetched];
  if (op->handler) {
    (this->*op->handler)();
    std::cout << "Opcode 0x" << std::hex << (int)opcode_fetched << "\n";
  } else
    std::cout << "Unimplemented opcode 0x" << std::hex << (int)opcode_fetched
              << "\n";
  t_states = op->t_states;
}

void Cpu::cycle() {
  if (t_states == 0) {
    uint8_t opcode = fetch();
    execute(opcode);
  }
  t_states--;
}

/***********************************************************
 * Private Helper Functions
 **********************************************************/

void Cpu::writeByteMemory(uint8_t data, uint16_t address) {
  memory[address] = data;
}

void Cpu::store8(uint8_t data, uint16_t address) {
  writeByteMemory(data, address);
}
void Cpu::store16(uint16_t data, uint16_t address) {
  uint8_t lo = data & 0x00FF;
  uint8_t hi = (data & 0xFF00) >> 8;
  writeByteMemory(lo, address);
  writeByteMemory(hi, address + 1);
}
/*
 * Write Flag
 * Perform a bit shift to write to a specific bit in the Flags (F) register.
 * The bit numbers are specified in the Flag enum class.
 */
void Cpu::writeFlag(Flag F, bool value) {
  if (value) {
    AF.lo |= 1 << static_cast<int>(F);
  } else {
    AF.lo &= ~(1 << static_cast<int>(F));
  }
  AF.lo &= 0xF0;
}

/*
 * Increment / Decrement register
 * Generic helper to increment or decrement a register and set flags accordingly
 */
void Cpu::incReg(uint8_t &reg) {
  uint8_t oldVal = reg;
  reg += 1;
  writeFlag(Flag::Z, reg == 0);
  writeFlag(Flag::N, 0);
  addSetH(oldVal, 1);
}

void Cpu::decReg(uint8_t &reg) {
  uint8_t oldVal = reg;
  reg -= 1;
  writeFlag(Flag::Z, reg == 0);
  writeFlag(Flag::N, 1);
  subSetH(oldVal, 1);
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

void Cpu::subSetH(uint8_t a, uint8_t b) {
  bool halfCarry = (a & 0x0F) < (b & 0x0F);
  writeFlag(Flag::H, halfCarry);
}

/*
 * RCLX
 * Takes a register and shifts it left.
 * The 7th bit is shifted out and rotated to bit 0.
 * It is also saved to flag C.
 */
void Cpu::RLCX(uint8_t &reg) {
  uint8_t oldBit7 = reg & 0x80;
  reg = (reg << 1) | (oldBit7 >> 7);
  writeFlag(Flag::Z, 0);
  writeFlag(Flag::N, 0);
  writeFlag(Flag::H, 0);
  writeFlag(Flag::C, oldBit7 != 0);
}

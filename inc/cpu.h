#pragma once

#include "opcode.h"
#include <array>
#include <cstdint>
#include <string>

/*
 * Flag values indicate bit position in the F register
 * Lower nibble of register is unused
 *  HI   LO
 * ZNHC XXXX
 */
enum class Flag : int { Z = 7, N = 6, H = 5, C = 4 };

/*
 * Reg16 - a 16 bit register
 * Actually a pair of 2 8-bit registers.
 *
 * For each register, the respective low and high bytes of each pair are:
 * lo   hi
 * A    F
 * B    C
 * D    E
 * H    L
 */
struct Reg16 {
  uint8_t lo;
  uint8_t hi;
  uint16_t getVal() { return hi << 8 | lo; }

  void loadReg(uint16_t val) {
    lo = val & 0x00FF;
    hi = (val & 0xFF00) >> 8;
  }
};

class Cpu {
private:
  Reg16 AF, BC, DE, HL, SP, PC;
  bool IME;
  int t_states;
  std::array<opcode, 256> opcodeTable;
  std::array<uint8_t, 65536> memory;

  /* Private helper functions */

  uint8_t fetch();
  uint16_t fetch16();
  void execute(uint8_t opcode);
  void writeByteMemory(uint8_t data, uint16_t address);
  uint8_t readByteMemory(uint16_t addr);
  void store8(uint8_t data, uint16_t address);
  void store16(uint16_t data, uint16_t address);
  uint8_t read8(uint16_t addr);
  uint16_t read16(uint16_t addr);
  void writeFlag(Flag F, bool value);
  bool readFlag(Flag F);
  void load8(uint16_t addr, uint8_t &dest);
  void loadReg(uint16_t addr, Reg16 &dest);
  void incReg(uint8_t &reg);
  void decReg(uint8_t &reg);
  void incReg16(Reg16 &reg);
  void decReg16(Reg16 &reg);
  void addReg16(Reg16 &source, Reg16 &dest);
  void addSetH(uint8_t a, uint8_t b);
  void subSetH(uint8_t a, uint8_t b);
  void rotateLeftThroughCarry(uint8_t &reg);
  void rotateRightThroughCarry(uint8_t &reg);
  void rotateLeft(uint8_t &reg);
  void rotateRight(uint8_t &reg);

  /* Opcode handlers */

  void handler_NOP(uint8_t opcode);
  void handler_LD_r16_d16(uint8_t opcode);
  void handler_INC_r8(uint8_t opcode);
  void handler_DEC_r8(uint8_t opcode);
  void handler_INC_DEC_r16(uint8_t opcode);

  void initOpcodeTable();
  void op_0x00();
  void op_0x01();
  void op_0x02();
  void op_0x03();
  void op_0x04();
  void op_0x05();
  void op_0x06();
  void op_0x07();
  void op_0x08();
  void op_0x09();
  void op_0x0A();
  void op_0x0B();
  void op_0x0C();
  void op_0x0D();
  void op_0x0E();
  void op_0x0F();

  void op_0x10();
  void op_0x11();
  void op_0x12();
  void op_0x13();
  void op_0x14();
  void op_0x15();
  void op_0x16();
  void op_0x17();
  void op_0x18();
  void op_0x19();
  void op_0x1A();
  void op_0x1B();
  void op_0x1C();
  void op_0x1D();
  void op_0x1E();
  void op_0x1F();

public:
  Cpu();
  int loadRom(const std::string &path);
  void cycle();
};

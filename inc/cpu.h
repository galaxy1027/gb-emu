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

  uint16_t GetVal() { return hi << 8 | lo; }

  void loadReg(uint16_t val) {
    lo = val & 0x00FF;
    hi = (val & 0xFF00) >> 8;
  }
};

class Cpu {
private:
  Reg16 AF, BC, DE, HL;
  uint16_t SP, PC;
  bool IME;
  int t_states;
  std::array<opcode, 256> opcodeTable;
  std::array<uint8_t, 65536> memory;

  void writeFlag(Flag F, bool value);
  void addSetH(uint8_t a, uint8_t b);
  void subSetH(uint8_t a, uint8_t b);
  uint8_t fetch();
  uint16_t fetch16();
  void execute(uint8_t opcode);
  void writeByteMemory(uint8_t data, uint16_t address);
  void store8(uint8_t data, uint16_t address);
  void store16(uint16_t data, uint16_t address);
  void incReg(uint8_t &reg);
  void decReg(uint8_t &reg);
  void RLCX(uint8_t &reg);

public:
  /* Opcode handlers */
  void op_0x00();
  void op_0x01();
  void op_0x02();
  void op_0x03();
  void op_0x04();
  void op_0x05();
  void op_0x06();
  void op_0x07();
  void op_0x08();

public:
  Cpu();
  int loadRom(const std::string &path);
  void cycle();
};

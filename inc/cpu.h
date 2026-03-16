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
  union {
    struct {
      uint8_t lo;
      uint8_t hi;
    };
    uint16_t val;
  };
};

class Cpu {
private:
  Reg16 AF, BC, DE, HL, SP, PC;
  bool IME, IME_Pending, stopped;
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
  void addReg16(uint16_t &source, uint16_t &dest);
  void addSetH(uint8_t a, uint8_t b);
  void add16SetH(uint16_t a, uint16_t b);
  void subSetH(uint8_t a, uint8_t b);
  void rotateLeftThroughCarry(uint8_t &reg);
  void rotateRightThroughCarry(uint8_t &reg);
  void rotateLeft(uint8_t &reg);
  void rotateRight(uint8_t &reg);
  uint8_t pop();
  uint16_t pop16();
  void push(uint8_t val);
  void push16(uint16_t val);

  uint8_t *decode_reg8(uint8_t opcode, char type);
  uint8_t *decode_reg8(uint8_t opcode);
  uint16_t *decode_reg16(uint8_t opcode);
  uint16_t *decode_reg16_stack_ops(uint8_t opcode);
  /* Opcode handlers */

  void handler_NOP(uint8_t opcode);
  void handler_LD_r8_d8(uint8_t opcode);
  void handler_LD_r16_d16(uint8_t opcode);
  void handler_LD_r8_r8(uint8_t opcode);
  void handler_LD_mem_A(uint8_t opcode);
  void handler_LD_A_mem(uint8_t opcode);
  void handler_LD_mem_SP(uint8_t opcode);
  void handler_INC_DEC_r8(uint8_t opcode);
  void handler_INC_DEC_r16(uint8_t opcode);
  void handler_ADD_HL_r16(uint8_t opcode);
  void handler_ADD_r8_r8(uint8_t opcode);
  void handler_ADC_r8_r8(uint8_t opcode);
  void handler_SUB_r8(uint8_t opcode);
  void handler_SBC_r8_r8(uint8_t opcode);
  void handler_AND_r8(uint8_t opcode);
  void handler_XOR_r8(uint8_t opcode);
  void handler_OR_r8(uint8_t opcode);
  void handler_CP_r8(uint8_t opcode);
  void handler_JR_s8(uint8_t opcode);
  void handler_RRC_r8(uint8_t opcode);
  void handler_RLC_r8(uint8_t opcode);
  void handler_RR_r8(uint8_t opcode);
  void handler_RL_r8(uint8_t opcode);
  void handler_DAA(uint8_t opcode);
  void handler_CPL(uint8_t opcode);
  void handler_XCF(uint8_t opcode);
  void handler_RET(uint8_t opcode);
  void handler_PUSH(uint8_t opcode);
  void handler_POP(uint8_t opcode);
  void handler_DI_EI(uint8_t opcode);
  void handler_STOP(uint8_t opcode);

  void initOpcodeTable();

public:
  Cpu();
  int loadRom(const std::string &path);
  void cycle();
};

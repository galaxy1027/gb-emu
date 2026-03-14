#include "opcode.h"
#include "cpu.h"
#include <iostream>

void Cpu::initOpcodeTable() {
  opcodeTable.fill({"INVALID", nullptr, 4});
  opcodeTable[0x00] = {"NOP", &Cpu::handler_NOP, 4};
  opcodeTable[0x01] = {"LD BC, d16", &Cpu::handler_LD_r16_d16, 12};
  opcodeTable[0x02] = {"LD (BC), A", &Cpu::op_0x02, 8};
  opcodeTable[0x03] = {"INC BC", &Cpu::handler_INC_r16, 8};
  opcodeTable[0x04] = {"INC B", &Cpu::op_0x04, 4};
  opcodeTable[0x05] = {"DEC B", &Cpu::op_0x05, 4};
  opcodeTable[0x06] = {"LD B, d8", &Cpu::op_0x06, 8};
  opcodeTable[0x07] = {"RLCA", &Cpu::op_0x07, 4};
  opcodeTable[0x08] = {"LD (a16), SP", &Cpu::op_0x08, 20};
  opcodeTable[0x09] = {"ADD HL, BC", &Cpu::op_0x09, 8};
  opcodeTable[0x0A] = {"LD A, (BC)", &Cpu::op_0x0A, 8};
  opcodeTable[0x0B] = {"DEC BC", &Cpu::handler_INC_DEC_r16, 8};
  opcodeTable[0x0C] = {"INC C", &Cpu::op_0x0C, 4};
  opcodeTable[0x0D] = {"DEC C", &Cpu::op_0x0D, 4};
  opcodeTable[0x0E] = {"LD C, d8", &Cpu::op_0x0E, 8};
  opcodeTable[0x0F] = {"RRCA", &Cpu::op_0x0F, 4};
  opcodeTable[0x10] = {"STOP", &Cpu::op_0x10, 4};
  opcodeTable[0x11] = {"LD DE, d16", &Cpu::op_0x11, 12};
  opcodeTable[0x12] = {"LD (DE), A", &Cpu::op_0x12, 8};
  opcodeTable[0x13] = {"INC DE", &Cpu::handler_INC_DEC_r16, 8};
  opcodeTable[0x14] = {"INC D", &Cpu::op_0x14, 4};
  opcodeTable[0x15] = {"DEC D", &Cpu::op_0x15, 4};
  opcodeTable[0x16] = {"LD D, d8", &Cpu::op_0x16, 8};
  opcodeTable[0x17] = {"RLA", &Cpu::op_0x17, 4};
  opcodeTable[0x18] = {"JR s8", &Cpu::op_0x18, 12};
  opcodeTable[0x19] = {"ADD HL, DE", &Cpu::op_0x19, 8};
  opcodeTable[0x1A] = {"LD A, (DE)", &Cpu::op_0x1A, 8};
  opcodeTable[0x1B] = {"DEC DE", &handler_INC_DEC_r16, 8};
  opcodeTable[0x1C] = {"INC E", &Cpu::op_0x1C, 4};
  opcodeTable[0x1D] = {"DEC E", &Cpu::op_0x1D, 4};
  opcodeTable[0x1E] = {"LD E, d8", &Cpu::op_0x1E, 8};
  opcodeTable[0x1F] = {"RRA", &Cpu::op_0x1F, 4};
}

void Cpu::handler_NOP(uint8_t opcode) {} // NOP

/*
 * LD r16, d16
 * Loading an immediate value into a register
 * To find the destination register, you just need to look at the upper 4 bits
 */
void Cpu::handler_LD_r16_d16(uint8_t opcode) {
  uint16_t d16 = fetch16();
  Reg16 *dest;
  switch (opcode >> 4 & 0x0F) {
  case 0x0:
    dest = &BC;
    break;
  case 0x1:
    dest = &DE;
    break;
  case 0x2:
    dest = &HL;
    break;
  case 0x3:
    dest = &SP;
    break;
  default:
    std::cerr << "Incorrect handler called\n";
    break;
  }
}

void Cpu::handler_INC_r8(uint8_t opcode) {
  uint8_t *dest;
  uint8_t upperOpcode = (opcode >> 4) & 0x0F, lowerOpcode = opcode & 0x0F;

  switch (upperOpcode) {
  case 0x00:
    dest = lowerOpcode == 0x4 ? &BC.hi : &BC.lo;
    break;
  case 0x01:
    dest = lowerOpcode == 0x4 ? &DE.hi : &DE.lo;
    break;
  case 0x02:
    dest = lowerOpcode == 0x4 ? &HL.hi : &HL.lo;
    break;
  case 0x03:
    dest = AF.hi;
    break;
  }
  incReg(*dest);
}

void Cpu::handler_DEC_r8(uint8_t opcode) {
  uint8_t *dest;
  uint8_t upperOpcode = (opcode >> 4) & 0x0F, lowerOpcode = opcode & 0x0F;

  switch (upperOpcode) {
  case 0x00:
    dest = lowerOpcode == 0x4 ? &BC.hi : &BC.lo;
    break;
  case 0x01:
    dest = lowerOpcode == 0x4 ? &DE.hi : &DE.lo;
    break;
  case 0x02:
    dest = lowerOpcode == 0x4 ? &HL.hi : &HL.lo;
    break;
  case 0x03:
    dest = AF.hi;
    break;
  }
  decReg(*dest);
}
void Cpu::op_0x01() { // LD BC, d16
  uint16_t d16 = fetch16();
  BC.loadReg(d16);
}
void Cpu::op_0x02() { // LD (BC), A
  uint16_t addr = BC.getVal();
  store8(AF.hi, addr);
}
void Cpu::op_0x03() { // INC BC
  uint16_t data = BC.getVal();
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
  rotateLeftThroughCarry(AF.hi);
}
void Cpu::op_0x08() { // LD (a16), SP
  uint16_t a16 = fetch16();
  store16(SP.getVal(), a16);
}

void Cpu::op_0x09() { // ADD HL, BC
  addReg16(BC, HL);
}

void Cpu::op_0x0A() { // LD A, (BC)
  load8(BC.getVal(), AF.hi);
}

void Cpu::op_0x0B() { // DEC BC
  decReg16(BC);
}
void Cpu::op_0x0C() { // INC C
  incReg(BC.lo);
}
void Cpu::op_0x0D() { // DEC C
  decReg(BC.lo);
}
void Cpu::op_0x0E() { // LD C ,d8
  uint8_t d8 = fetch();
  BC.lo = d8;
}
void Cpu::op_0x0F() { // RRCA
  rotateRightThroughCarry(AF.hi);
}

void Cpu::op_0x10() { // STOP
}
void Cpu::op_0x11() { // LD DE, d16
  uint16_t d16 = fetch16();
  DE.loadReg(d16);
}
void Cpu::op_0x12() { // LD (DE), A
  uint16_t addr = DE.getVal();
  store8(AF.hi, addr);
}
void Cpu::op_0x13() { // INC DE
  incReg16(DE);
}
void Cpu::op_0x14() { // INC D
  incReg(DE.hi);
}
void Cpu::op_0x15() { // DEC D
  decReg(DE.hi);
}
void Cpu::op_0x16() { // LD D, d8
  uint8_t d8 = fetch();
  DE.hi = d8;
}
void Cpu::op_0x17() { // RLA
  rotateLeft(AF.hi);
}
void Cpu::op_0x18() { // JR s8
  PC.loadReg(PC.getVal() + static_cast<int8_t>(fetch()));
}
void Cpu::op_0x19() { // ADD HL, DE
  addReg16(DE, HL);
}
void Cpu::op_0x1A() {}
void Cpu::op_0x1B() { // DEC DE
  decReg16(DE);
}
void Cpu::op_0x1C() { // INC E
  incReg(DE.lo);
}
void Cpu::op_0x1D() { // DEC E
  decReg(DE.lo);
}
void Cpu::op_0x1E() { // LD E, d8
  uint8_t d8 = fetch();
  DE.lo = d8;
}
void Cpu::op_0x1F() { // RRA
  rotateRight(AF.hi);
}

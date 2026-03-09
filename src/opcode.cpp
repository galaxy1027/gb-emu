#include "opcode.h"
#include "cpu.h"

void initOpcodeTable(std::array<opcode, 256> &table) {
  table.fill({"INVALID", nullptr, 4});
  table[0x00] = {"NOP", &Cpu::op_0x00, 4};
  table[0x01] = {"LD BC, d16", &Cpu::op_0x01, 12};
  table[0x02] = {"LD (BC), A", &Cpu::op_0x02, 8};
  table[0x03] = {"INC BC", &Cpu::op_0x03, 8};
  table[0x04] = {"INC B", &Cpu::op_0x04, 4};
  table[0x05] = {"DEC B", &Cpu::op_0x05, 4};
  table[0x06] = {"LD B, d8", &Cpu::op_0x06, 8};
  table[0x07] = {"RLCA", &Cpu::op_0x07, 4};
  table[0x08] = {"LD (a16), SP", &Cpu::op_0x08, 20};
}

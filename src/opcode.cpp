#include "opcode.h"
#include "cpu.h"
#include <iostream>

void Cpu::initOpcodeTable() {
  opcodeTable.fill({"INVALID", nullptr, 4});
  opcodeTable[0x00] = {"NOP", &Cpu::handler_NOP, 4};
  opcodeTable[0x01] = {"LD BC, d16", &Cpu::handler_LD_r16_d16, 12};
  opcodeTable[0x02] = {"LD (BC), A", &Cpu::handler_LD_mem_A, 8};
  opcodeTable[0x03] = {"INC BC", &Cpu::handler_INC_DEC_r16, 8};
  opcodeTable[0x04] = {"INC B", &Cpu::handler_INC_DEC_r8, 4};
  opcodeTable[0x05] = {"DEC B", &Cpu::handler_INC_DEC_r8, 4};
  opcodeTable[0x06] = {"LD B, d8", &Cpu::handler_LD_r8_d8, 8};
  opcodeTable[0x07] = {"RLCA", &Cpu::handler_RLC_r8, 4};
  opcodeTable[0x08] = {"LD (a16), SP", &Cpu::handler_LD_mem_SP, 20};
  opcodeTable[0x09] = {"ADD HL, BC", &Cpu::handler_ADD_HL_r16, 8};
  opcodeTable[0x0A] = {"LD A, (BC)", &Cpu::handler_LD_A_mem, 8};
  opcodeTable[0x0B] = {"DEC BC", &Cpu::handler_INC_DEC_r16, 8};
  opcodeTable[0x0C] = {"INC C", &Cpu::handler_INC_DEC_r8, 4};
  opcodeTable[0x0D] = {"DEC C", &Cpu::handler_INC_DEC_r8, 4};
  opcodeTable[0x0E] = {"LD C, d8", &Cpu::handler_LD_r8_d8, 8};
  opcodeTable[0x0F] = {"RRCA", &Cpu::handler_RRC_r8, 4};

  opcodeTable[0x10] = {"STOP", &Cpu::handler_STOP, 4};
  opcodeTable[0x11] = {"LD DE, d16", &Cpu::handler_LD_r16_d16, 12};
  opcodeTable[0x12] = {"LD (DE), A", &Cpu::handler_LD_mem_A, 8};
  opcodeTable[0x13] = {"INC DE", &Cpu::handler_INC_DEC_r16, 8};
  opcodeTable[0x14] = {"INC D", &Cpu::handler_INC_DEC_r8, 4};
  opcodeTable[0x15] = {"DEC D", &Cpu::handler_INC_DEC_r8, 4};
  opcodeTable[0x16] = {"LD D, d8", &Cpu::handler_LD_r8_d8, 8};
  opcodeTable[0x17] = {"RLA", &Cpu::handler_RL_r8, 4};
  opcodeTable[0x18] = {"JR s8", &Cpu::handler_JR_s8, 8};
  opcodeTable[0x19] = {"ADD HL, DE", &Cpu::handler_ADD_HL_r16, 8};
  opcodeTable[0x1A] = {"LD A, (DE)", &Cpu::handler_LD_A_mem, 8};
  opcodeTable[0x1B] = {"DEC DE", &Cpu::handler_INC_DEC_r16, 8};
  opcodeTable[0x1C] = {"INC E", &Cpu::handler_INC_DEC_r8, 4};
  opcodeTable[0x1D] = {"DEC E", &Cpu::handler_INC_DEC_r8, 4};
  opcodeTable[0x1E] = {"LD E, d8", &Cpu::handler_LD_r8_d8, 8};
  opcodeTable[0x1F] = {"RRA", &Cpu::handler_RR_r8, 4};

  opcodeTable[0x20] = {"JR NZ, s8", &Cpu::handler_JR_s8, 8};
  opcodeTable[0x21] = {"LD HL, d16", &Cpu::handler_LD_r16_d16, 12};
  opcodeTable[0x22] = {"LD (HL+), A", &Cpu::handler_LD_mem_A, 8};
  opcodeTable[0x23] = {"INC HL", &Cpu::handler_INC_DEC_r16, 8};
  opcodeTable[0x24] = {"INC H", &Cpu::handler_INC_DEC_r8, 4};
  opcodeTable[0x25] = {"DEC H", &Cpu::handler_INC_DEC_r8, 4};
  opcodeTable[0x26] = {"LD H, d8", &Cpu::handler_LD_r8_d8, 8};
  opcodeTable[0x27] = {"DAA", &Cpu::handler_DAA, 4};
  opcodeTable[0x28] = {"JR Z, s8", &Cpu::handler_JR_s8, 8};
  opcodeTable[0x29] = {"ADD HL, HL", &Cpu::handler_ADD_HL_r16, 8};
  opcodeTable[0x2A] = {"LD A, (HL+)", &Cpu::handler_LD_A_mem, 8};
  opcodeTable[0x2B] = {"DEC HL", &Cpu::handler_INC_DEC_r16, 8};
  opcodeTable[0x2C] = {"INC L", &Cpu::handler_INC_DEC_r8, 4};
  opcodeTable[0x2D] = {"DEC L", &Cpu::handler_INC_DEC_r8, 4};
  opcodeTable[0x2E] = {"LD L, d8", &Cpu::handler_LD_r8_d8, 8};
  opcodeTable[0x2F] = {"CPL", &Cpu::handler_CPL, 4};

  opcodeTable[0x30] = {"JR NZ, s8", &Cpu::handler_JR_s8, 8};
  opcodeTable[0x31] = {"LD SP, d16", &Cpu::handler_LD_r16_d16, 12};
  opcodeTable[0x32] = {"LD (HL-), A", &Cpu::handler_LD_mem_A, 8};
  opcodeTable[0x33] = {"INC SP", &Cpu::handler_INC_DEC_r16, 8};
  opcodeTable[0x34] = {"INC (HL)", &Cpu::handler_INC_DEC_r8, 12};
  opcodeTable[0x35] = {"DEC (HL)", &Cpu::handler_INC_DEC_r8, 12};
  opcodeTable[0x36] = {"LD (HL), d8", &Cpu::handler_LD_r8_d8, 12};
  opcodeTable[0x37] = {"SCF", &Cpu::handler_XCF, 4};
  opcodeTable[0x38] = {"JR C, s8", &Cpu::handler_JR_s8, 8};
  opcodeTable[0x39] = {"ADD HL, SP", &Cpu::handler_ADD_HL_r16, 8};
  opcodeTable[0x3A] = {"LD A, (HL-)", &Cpu::handler_LD_A_mem, 8};
  opcodeTable[0x3B] = {"DEC SP", &Cpu::handler_INC_DEC_r16, 8};
  opcodeTable[0x3C] = {"INC A", &Cpu::handler_INC_DEC_r8, 4};
  opcodeTable[0x3D] = {"DEC A", &Cpu::handler_INC_DEC_r8, 4};
  opcodeTable[0x3E] = {"LD A, d8", &Cpu::handler_LD_r8_d8, 8};
  opcodeTable[0x3F] = {"CCF", &Cpu::handler_XCF, 4};

  opcodeTable[0x40] = {"LD B, B", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x41] = {"LD B, C", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x42] = {"LD B, D", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x43] = {"LD B, E", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x44] = {"LD B, H", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x45] = {"LD B, L", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x46] = {"LD B, (HL)", &Cpu::handler_LD_r8_r8, 8};
  opcodeTable[0x47] = {"LD B, A", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x48] = {"LD C, B", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x49] = {"LD C, C", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x4A] = {"LD C, D", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x4B] = {"LD C, E", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x4C] = {"LD C, H", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x4D] = {"LD C, L", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x4E] = {"LD C, (HL)", &Cpu::handler_LD_r8_r8, 8};
  opcodeTable[0x4F] = {"LD C, A", &Cpu::handler_LD_r8_r8, 4};

  opcodeTable[0x50] = {"LD D, B", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x51] = {"LD D, C", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x52] = {"LD D, D", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x53] = {"LD D, E", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x54] = {"LD D, H", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x55] = {"LD D, L", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x56] = {"LD D, (HL)", &Cpu::handler_LD_r8_r8, 8};
  opcodeTable[0x57] = {"LD D, A", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x58] = {"LD E, B", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x59] = {"LD E, C", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x5A] = {"LD E, D", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x5B] = {"LD E, E", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x5C] = {"LD E, H", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x5D] = {"LD E, L", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x5E] = {"LD E, (HL)", &Cpu::handler_LD_r8_r8, 8};
  opcodeTable[0x5F] = {"LD E, A", &Cpu::handler_LD_r8_r8, 4};

  opcodeTable[0x60] = {"LD H, B", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x61] = {"LD H, C", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x62] = {"LD H, D", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x63] = {"LD H, E", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x64] = {"LD H, H", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x65] = {"LD H, L", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x66] = {"LD H, (HL)", &Cpu::handler_LD_r8_r8, 8};
  opcodeTable[0x67] = {"LD H, A", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x68] = {"LD L, B", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x69] = {"LD L, C", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x6A] = {"LD L, D", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x6B] = {"LD L, E", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x6C] = {"LD L, H", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x6D] = {"LD L, L", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x6E] = {"LD L, (HL)", &Cpu::handler_LD_r8_r8, 8};
  opcodeTable[0x6F] = {"LD L, A", &Cpu::handler_LD_r8_r8, 4};

  opcodeTable[0x70] = {"LD (HL), B", &Cpu::handler_LD_r8_r8, 8};
  opcodeTable[0x71] = {"LD (HL), C", &Cpu::handler_LD_r8_r8, 8};
  opcodeTable[0x72] = {"LD (HL), D", &Cpu::handler_LD_r8_r8, 8};
  opcodeTable[0x73] = {"LD (HL), E", &Cpu::handler_LD_r8_r8, 8};
  opcodeTable[0x74] = {"LD (HL), H", &Cpu::handler_LD_r8_r8, 8};
  opcodeTable[0x75] = {"LD (HL), L", &Cpu::handler_LD_r8_r8, 8};
  opcodeTable[0x76] = {"HALT", nullptr, 4};
  opcodeTable[0x77] = {"LD (HL), A", &Cpu::handler_LD_r8_r8, 8};
  opcodeTable[0x78] = {"LD A, B", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x79] = {"LD A, C", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x7A] = {"LD A, D", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x7B] = {"LD A, E", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x7C] = {"LD A, H", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x7D] = {"LD A, L", &Cpu::handler_LD_r8_r8, 4};
  opcodeTable[0x7E] = {"LD A, (HL)", &Cpu::handler_LD_r8_r8, 8};
  opcodeTable[0x7F] = {"LD A, A", &Cpu::handler_LD_r8_r8, 4};

  opcodeTable[0x80] = {"ADD A, B", &Cpu::handler_ADD_r8_r8, 4};
  opcodeTable[0x81] = {"ADD A, C", &Cpu::handler_ADD_r8_r8, 4};
  opcodeTable[0x82] = {"ADD A, D", &Cpu::handler_ADD_r8_r8, 4};
  opcodeTable[0x83] = {"ADD A, E", &Cpu::handler_ADD_r8_r8, 4};
  opcodeTable[0x84] = {"ADD A, H", &Cpu::handler_ADD_r8_r8, 4};
  opcodeTable[0x85] = {"ADD A, L", &Cpu::handler_ADD_r8_r8, 4};
  opcodeTable[0x86] = {"ADD A, (HL)", &Cpu::handler_ADD_r8_r8, 8};
  opcodeTable[0x87] = {"ADD A, A", &Cpu::handler_ADD_r8_r8, 4};
  opcodeTable[0x88] = {"ADC A, B", &Cpu::handler_ADC_r8_r8, 4};
  opcodeTable[0x89] = {"ADC A, C", &Cpu::handler_ADC_r8_r8, 4};
  opcodeTable[0x8A] = {"ADC A, D", &Cpu::handler_ADC_r8_r8, 4};
  opcodeTable[0x8B] = {"ADC A, E", &Cpu::handler_ADC_r8_r8, 4};
  opcodeTable[0x8C] = {"ADC A, H", &Cpu::handler_ADC_r8_r8, 4};
  opcodeTable[0x8D] = {"ADC A, L", &Cpu::handler_ADC_r8_r8, 4};
  opcodeTable[0x8E] = {"ADC A, (HL)", &Cpu::handler_ADC_r8_r8, 8};
  opcodeTable[0x8F] = {"ADC A, A", &Cpu::handler_ADC_r8_r8, 4};

  opcodeTable[0x90] = {"SUB B", &Cpu::handler_SUB_r8, 4};
  opcodeTable[0x91] = {"SUB C", &Cpu::handler_SUB_r8, 4};
  opcodeTable[0x92] = {"SUB D", &Cpu::handler_SUB_r8, 4};
  opcodeTable[0x93] = {"SUB E", &Cpu::handler_SUB_r8, 4};
  opcodeTable[0x94] = {"SUB H", &Cpu::handler_SUB_r8, 4};
  opcodeTable[0x95] = {"SUB L", &Cpu::handler_SUB_r8, 4};
  opcodeTable[0x96] = {"SUB (HL)", &Cpu::handler_SUB_r8, 8};
  opcodeTable[0x97] = {"SUB A", &Cpu::handler_SUB_r8, 4};
  opcodeTable[0x98] = {"SBC A, B", &Cpu::handler_SBC_r8_r8, 4};
  opcodeTable[0x99] = {"SBC A, C", &Cpu::handler_SBC_r8_r8, 4};
  opcodeTable[0x9A] = {"SBC A, D", &Cpu::handler_SBC_r8_r8, 4};
  opcodeTable[0x9B] = {"SBC A, E", &Cpu::handler_SBC_r8_r8, 4};
  opcodeTable[0x9C] = {"SBC A, H", &Cpu::handler_SBC_r8_r8, 4};
  opcodeTable[0x9D] = {"SBC A, L", &Cpu::handler_SBC_r8_r8, 4};
  opcodeTable[0x9E] = {"SBC A, (HL)", &Cpu::handler_SBC_r8_r8, 8};
  opcodeTable[0x9F] = {"SBC A, A", &Cpu::handler_SBC_r8_r8, 4};

  opcodeTable[0xA0] = {"AND B", &Cpu::handler_AND_r8, 4};
  opcodeTable[0xA1] = {"AND C", &Cpu::handler_AND_r8, 4};
  opcodeTable[0xA2] = {"AND D", &Cpu::handler_AND_r8, 4};
  opcodeTable[0xA3] = {"AND E", &Cpu::handler_AND_r8, 4};
  opcodeTable[0xA4] = {"AND H", &Cpu::handler_AND_r8, 4};
  opcodeTable[0xA5] = {"AND L", &Cpu::handler_AND_r8, 4};
  opcodeTable[0xA6] = {"AND (HL)", &Cpu::handler_AND_r8, 8};
  opcodeTable[0xA7] = {"AND A", &Cpu::handler_AND_r8, 4};
  opcodeTable[0xA8] = {"XOR B", &Cpu::handler_XOR_r8, 4};
  opcodeTable[0xA9] = {"XOR C", &Cpu::handler_XOR_r8, 4};
  opcodeTable[0xAA] = {"XOR D", &Cpu::handler_XOR_r8, 4};
  opcodeTable[0xAB] = {"XOR E", &Cpu::handler_XOR_r8, 4};
  opcodeTable[0xAC] = {"XOR H", &Cpu::handler_XOR_r8, 4};
  opcodeTable[0xAD] = {"XOR L", &Cpu::handler_XOR_r8, 4};
  opcodeTable[0xAE] = {"XOR (HL)", &Cpu::handler_XOR_r8, 8};
  opcodeTable[0xAF] = {"XOR A", &Cpu::handler_XOR_r8, 4};

  opcodeTable[0xB0] = {"OR B", &Cpu::handler_OR_r8, 4};
  opcodeTable[0xB1] = {"OR C", &Cpu::handler_OR_r8, 4};
  opcodeTable[0xB2] = {"OR D", &Cpu::handler_OR_r8, 4};
  opcodeTable[0xB3] = {"OR E", &Cpu::handler_OR_r8, 4};
  opcodeTable[0xB4] = {"OR H", &Cpu::handler_OR_r8, 4};
  opcodeTable[0xB5] = {"OR L", &Cpu::handler_OR_r8, 4};
  opcodeTable[0xB6] = {"OR (HL)", &Cpu::handler_OR_r8, 8};
  opcodeTable[0xB7] = {"OR A", &Cpu::handler_OR_r8, 4};
  opcodeTable[0xB8] = {"CP B", &Cpu::handler_CP_r8, 4};
  opcodeTable[0xB9] = {"CP C", &Cpu::handler_CP_r8, 4};
  opcodeTable[0xBA] = {"CP D", &Cpu::handler_CP_r8, 4};
  opcodeTable[0xBB] = {"CP E", &Cpu::handler_CP_r8, 4};
  opcodeTable[0xBC] = {"CP H", &Cpu::handler_CP_r8, 4};
  opcodeTable[0xBD] = {"CP L", &Cpu::handler_CP_r8, 4};
  opcodeTable[0xBE] = {"CP (HL)", &Cpu::handler_CP_r8, 8};
  opcodeTable[0xBF] = {"CP A", &Cpu::handler_CP_r8, 4};

  opcodeTable[0xC0] = {"RET NZ", &Cpu::handler_RET, 8};
  opcodeTable[0xC1] = {"POP BC", &Cpu::handler_POP, 12};
  opcodeTable[0xC2] = {"JP NZ, a16", nullptr, 0};
  opcodeTable[0xC3] = {"JP a16", nullptr, 16};
  opcodeTable[0xC4] = {"CALL NZ, a16", nullptr, 0};
  opcodeTable[0xC5] = {"PUSH BC", &Cpu::handler_PUSH, 16};
  opcodeTable[0xC6] = {"ADD A, d8", nullptr, 8};
  opcodeTable[0xC7] = {"RST 0", nullptr, 16};
  opcodeTable[0xC8] = {"RET Z", &Cpu::handler_RET, 8};
  opcodeTable[0xC9] = {"RET", &Cpu::handler_RET, 8};
  opcodeTable[0xCA] = {"JP Z, a16", nullptr, 0};
  opcodeTable[0xCB] = {"UNDEFINED", nullptr, 0};
  opcodeTable[0xCC] = {"CALL Z, a16", nullptr, 0};
  opcodeTable[0xCD] = {"CALL a16", nullptr, 24};
  opcodeTable[0xCE] = {"ADC A, d8", nullptr, 8};
  opcodeTable[0xCF] = {"RST 1", nullptr, 16};

  opcodeTable[0xD0] = {"RET NC", &Cpu::handler_RET, 8};
  opcodeTable[0xD1] = {"POP DE", &Cpu::handler_POP, 12};
  opcodeTable[0xD2] = {"JP NC, a16", nullptr, 0};
  opcodeTable[0xD3] = {"UNDEFINED", nullptr, 0};
  opcodeTable[0xD4] = {"CALL NC, a16", nullptr, 0};
  opcodeTable[0xD5] = {"PUSH DE", &Cpu::handler_PUSH, 16};
  opcodeTable[0xD6] = {"SUB d8", nullptr, 8};
  opcodeTable[0xD7] = {"RST 2", nullptr, 16};
  opcodeTable[0xD8] = {"RET C", &Cpu::handler_RET, 8};
  opcodeTable[0xD9] = {"RETI", nullptr, 16};
  opcodeTable[0xDA] = {"JP C, a16", nullptr, 0};
  opcodeTable[0xDB] = {"UNDEFINED", nullptr, 0};
  opcodeTable[0xDC] = {"CALL C, a16", nullptr, 0};
  opcodeTable[0xDD] = {"UNDEFINED", nullptr, 0};
  opcodeTable[0xDE] = {"SBC A, d8", nullptr, 8};
  opcodeTable[0xDF] = {"RST 3", nullptr, 16};

  opcodeTable[0xE0] = {"LD (a8), A", nullptr, 12};
  opcodeTable[0xE1] = {"POP HL", &Cpu::handler_POP, 12};
  opcodeTable[0xE2] = {"LD (C), A", nullptr, 8};
  opcodeTable[0xE3] = {"UNDEFINED", nullptr, 0};
  opcodeTable[0xE4] = {"UNDEFINED", nullptr, 0};
  opcodeTable[0xE5] = {"PUSH HL", &Cpu::handler_PUSH, 16};
  opcodeTable[0xE6] = {"AND d8", nullptr, 8};
  opcodeTable[0xE7] = {"RST 4", nullptr, 16};
  opcodeTable[0xE8] = {"ADD SP, s8", nullptr, 16};
  opcodeTable[0xE9] = {"JP HL", nullptr, 4};
  opcodeTable[0xEA] = {"LD (a16), A", nullptr, 16};
  opcodeTable[0xEB] = {"UNDEFINED", nullptr, 0};
  opcodeTable[0xEC] = {"UNDEFINED", nullptr, 0};
  opcodeTable[0xED] = {"UNDEFINED", nullptr, 0};
  opcodeTable[0xEE] = {"XOR d8", nullptr, 8};
  opcodeTable[0xEF] = {"RST 5", nullptr, 16};

  opcodeTable[0xF0] = {"LD A, (a8)", nullptr, 12};
  opcodeTable[0xF1] = {"POP AF", &Cpu::handler_POP, 12};
  opcodeTable[0xF2] = {"LD A, (C)", nullptr, 8};
  opcodeTable[0xF3] = {"DI", &Cpu::handler_DI_EI, 4};
  opcodeTable[0xF4] = {"UNDEFINED", nullptr, 0};
  opcodeTable[0xF5] = {"PUSH AF", &Cpu::handler_PUSH, 16};
  opcodeTable[0xF6] = {"OR d8", nullptr, 8};
  opcodeTable[0xF7] = {"RST 6", nullptr, 16};
  opcodeTable[0xF8] = {"LD HL, SP+s8", nullptr, 12};
  opcodeTable[0xF9] = {"LD SP, HL", nullptr, 8};
  opcodeTable[0xFA] = {"LD A, (a16)", nullptr, 16};
  opcodeTable[0xFB] = {"EI", &Cpu::handler_DI_EI, 4};
  opcodeTable[0xFC] = {"UNDEFINED", nullptr, 0};
  opcodeTable[0xFD] = {"UNDEFINED", nullptr, 0};
  opcodeTable[0xFE] = {"CP d8", nullptr, 8};
  opcodeTable[0xFF] = {"RST 7", nullptr, 16};
}

/*
 *
 * Decode 8-bit register
 * When decoding instructions for 8 bit registers, they follow this format:
 * xx   xxx    xxx
 * (instruction) (dest register) (source register)
 *
 * This function lets you extract either the dest or source register depending
 * on the flag value. Source is assumed unless 'd' is supplied.
 */
uint8_t *Cpu::decode_reg8(uint8_t opcode, char type) {
  uint8_t *reg;
  if (type == 'd') {
    reg = decode_reg8(opcode >> 3);
  } else {
    reg = decode_reg8(opcode);
  }
  return reg;
}

/*
 * Decoder for 8-bit registers
 *
 * The opcodes determine a register by encoding a value in the lower 3 bits.
 * This decoder inspects those bits and returns a pointer to the coresponding
 * register.
 */
uint8_t *Cpu::decode_reg8(uint8_t opcode) {
  uint8_t *reg = nullptr;
  uint8_t regCode;
  regCode = opcode & 0b111;

  switch (regCode) {
  case 0x0:
    reg = &BC.hi;
    break;
  case 0x1:
    reg = &BC.lo;
    break;
  case 0x2:
    reg = &DE.hi;
    break;
  case 0x3:
    reg = &DE.lo;
    break;
  case 0x4:
    reg = &HL.hi;
    break;
  case 0x5:
    reg = &HL.lo;
    break;
  case 0x7:
    reg = &AF.hi;
    break;
  }
  return reg;
}
/*
 * For 16 bit operations, aside from some stack operations, the format is
 * 00   xx  xxxx
 * (empty) (register) (operation)
 *
 * there are no opcodes that use both a source and destination 16-bit reg.
 */
uint16_t *Cpu::decode_reg16(uint8_t opcode) {
  uint16_t *reg = nullptr;
  uint8_t regCode = (opcode >> 4) & 0b11;

  switch (regCode) {
  case 0x0:
    reg = &BC.val;
    break;
  case 0x1:
    reg = &DE.val;
    break;
  case 0x2:
    reg = &HL.val;
    break;
  case 0x3:
    reg = &SP.val;
    break;
  }
  return reg;
}

uint16_t *Cpu::decode_reg16_stack_ops(uint8_t opcode) {
  uint16_t *reg = nullptr;

  switch ((opcode >> 4) & 0x0F) {
  case 0xC:
    reg = &BC.val;
    break;
  case 0xD:
    reg = &DE.val;
    break;
  case 0xE:
    reg = &HL.val;
    break;
  case 0xF:
    reg = &AF.val;
    break;
  }
  return reg;
}

void Cpu::handler_NOP(uint8_t opcode) {} // NOP, do nothing

/*
 * LD r8, d8
 *
 * Load an immediate value into a register.
 * Decode a destination register and load fetched byte into it.
 */
void Cpu::handler_LD_r8_d8(uint8_t opcode) {
  uint8_t *dest = decode_reg8(opcode, 'd');
  uint8_t data = fetch();
  *dest = data;
}
/*
 * LD r16, d16
 * Loading an immediate value into a register (16-bit version)
 * Works the same as LD r8, d8, except fetches 2 bytes.
 */
void Cpu::handler_LD_r16_d16(uint8_t opcode) {
  uint16_t d16 = fetch16();
  uint16_t *dest = decode_reg16(opcode);
  *dest = d16;
}

void Cpu::handler_LD_r8_r8(uint8_t opcode) {
  uint8_t *src = decode_reg8(opcode, 's');
  uint8_t *dst = decode_reg8(opcode, 'd');
  *dst = *src;
}

void Cpu::handler_LD_mem_A(uint8_t opcode) {
  uint16_t ptr;
  switch ((opcode >> 4) & 0b11) {
  case 0x0:
    ptr = BC.val;
    break;
  case 0x1:
    ptr = DE.val;
    break;
  case 0x2:
    ptr = HL.val;
    HL.val++;
    break;
  case 0x3:
    ptr = HL.val;
    HL.val--;
    break;
  }
  writeByteMemory(AF.hi, ptr);
}

void Cpu::handler_LD_A_mem(uint8_t opcode) {
  uint16_t ptr;
  switch ((opcode >> 4) & 0b11) {
  case 0x0:
    ptr = BC.val;
    break;
  case 0x1:
    ptr = DE.val;
    break;
  case 0x2:
    ptr = HL.val;
    HL.val++;
    break;
  case 0x3:
    ptr = HL.val;
    HL.val--;
    break;
  }
  AF.hi = readByteMemory(ptr);
}

void Cpu::handler_LD_mem_SP(uint8_t opcode) {
  uint16_t ptr = fetch16();
  store16(SP.val, ptr);
}

/*
 * Increment / decrement handlers
 * The lowest bit determines if the opcode is incrementing or decrementing.
 * Decode this and the destination register to change.
 */
void Cpu::handler_INC_DEC_r8(uint8_t opcode) {
  uint8_t *dest = decode_reg8(opcode, 'd');
  uint8_t oldVal = *dest;
  bool increment = !(opcode & 0x01);
  increment ? (*dest)++ : (*dest)--;
  writeFlag(Flag::Z, *dest == 0);
  writeFlag(Flag::N, !increment);
  increment ? addSetH(oldVal, 1) : subSetH(oldVal, 1);
}

void Cpu::handler_INC_DEC_r16(uint8_t opcode) {
  uint16_t *dest = decode_reg16(opcode);
  bool increment = (opcode & 0x0F) == 0x03;
  increment ? (*dest)++ : (*dest)--;
}

void Cpu::handler_ADD_HL_r16(uint8_t opcode) {
  uint16_t *src = decode_reg16(opcode);
  addReg16(HL.val, *src);
}
void Cpu::handler_ADD_r8_r8(uint8_t opcode) {
  uint8_t *src = decode_reg8(opcode, 's');
  uint8_t *dst = decode_reg8(opcode, 'd');
  uint16_t sum = *src + *dst;
  uint8_t result = sum & 0x00FF;
  writeFlag(Flag::Z, result == 0);
  writeFlag(Flag::N, 0);
  addSetH(*src, *dst);
  writeFlag(Flag::C, sum > 0x00FF);
  *dst = result;
}
void Cpu::handler_ADC_r8_r8(uint8_t opcode) {
  uint8_t *src = decode_reg8(opcode, 's');
  uint8_t *dst = decode_reg8(opcode, 'd');
  uint8_t carry = readFlag(Flag::C) ? 1 : 0;
  bool halfCarry = ((*dst & 0x0F) + (*src & 0x0F) + carry) > 0x0F;
  uint16_t sum = *src + *dst + carry;
  uint8_t result = sum & 0x00FF;
  writeFlag(Flag::Z, result == 0);
  writeFlag(Flag::N, 0);
  writeFlag(Flag::H, halfCarry);
  writeFlag(Flag::C, sum > 0x00FF);
  *dst = result;
}

void Cpu::handler_SUB_r8(uint8_t opcode) {
  uint8_t *src = decode_reg8(opcode, 's');
  uint8_t diff = AF.hi - *src;
  writeFlag(Flag::Z, diff == 0);
  writeFlag(Flag::N, 1);
  subSetH(AF.hi, *src);
  writeFlag(Flag::C, AF.hi < *src);
  AF.hi = diff;
}

void Cpu::handler_SBC_r8_r8(uint8_t opcode) {
  uint8_t *src = decode_reg8(opcode, 's');
  uint8_t *dst = decode_reg8(opcode, 'd');
  uint8_t carry = readFlag(Flag::C) == true ? 1 : 0;
  uint8_t diff = *dst - *src - carry;
  writeFlag(Flag::Z, diff == 0);
  writeFlag(Flag::N, 1);
  writeFlag(Flag::H, (*dst & 0x0F) < ((*src & 0x0F) + carry));
  writeFlag(Flag::C, *dst < (*src + carry));
  *dst = diff;
}

void Cpu::handler_AND_r8(uint8_t opcode) {
  AF.hi &= *(decode_reg8(opcode));
  writeFlag(Flag::Z, AF.hi == 0);
  writeFlag(Flag::N, 0);
  writeFlag(Flag::H, 1);
  writeFlag(Flag::C, 0);
}
void Cpu::handler_XOR_r8(uint8_t opcode) {
  AF.hi ^= *(decode_reg8(opcode));
  writeFlag(Flag::Z, AF.hi == 0);
  writeFlag(Flag::N, 0);
  writeFlag(Flag::H, 0);
  writeFlag(Flag::C, 0);
}
void Cpu::handler_OR_r8(uint8_t opcode) {
  AF.hi |= *(decode_reg8(opcode));
  writeFlag(Flag::Z, AF.hi == 0);
  writeFlag(Flag::N, 0);
  writeFlag(Flag::H, 0);
  writeFlag(Flag::C, 0);
}
void Cpu::handler_CP_r8(uint8_t opcode) {
  uint8_t *src = decode_reg8(opcode, 's');
  uint8_t diff = AF.hi - *src;
  writeFlag(Flag::Z, diff == 0);
  writeFlag(Flag::N, 1);
  subSetH(AF.hi, *src);
  writeFlag(Flag::C, AF.hi < *src);
}
/*
 * Jump s8
 * Moves the PC by a signed offset if a jump occurs. Flags determine this
 * depeding on the opcode
 */
void Cpu::handler_JR_s8(uint8_t opcode) {
  int8_t jumpOffset = static_cast<int8_t>(fetch());
  bool jump = false;

  switch (opcode) {
  case 0x18:
    jump = true;
    break;
  case 0x28:
    jump = readFlag(Flag::Z);
    break;
  case 0x38:
    jump = readFlag(Flag::C);
    break;
  case 0x20:
    jump = !readFlag(Flag::Z);
    break;
  case 0x30:
    jump = !readFlag(Flag::C);
    break;
  default:
    std::cerr << "Could not determine if jump happens\n";
    break;
  }
  if (jump) {
    PC.val += jumpOffset;
    t_states += 4;
  }
}

/*
 * Rotate handlers
 *
 * Decode the register based on opcode, and perform the proper bit rotation.
 */
void Cpu::handler_RRC_r8(uint8_t opcode) {
  uint8_t *reg = decode_reg8(opcode);
  rotateRightThroughCarry(*reg);
}
void Cpu::handler_RLC_r8(uint8_t opcode) {
  uint8_t *reg = decode_reg8(opcode);
  rotateLeftThroughCarry(*reg);
}
void Cpu::handler_RR_r8(uint8_t opcode) {
  uint8_t *reg = decode_reg8(opcode);
  rotateRight(*reg);
}
void Cpu::handler_RL_r8(uint8_t opcode) {
  uint8_t *reg = decode_reg8(opcode);
  rotateLeft(*reg);
}

/*
 * DAA handler
 * Adjust the A register to a BCD number after BCD addition and subtraction
 * operations
 *
 * For example, fix 0x25 + 0x37 = 0x5C to be 0x62 because (decimal) 25 + 37 = 52
 */
void Cpu::handler_DAA(uint8_t opcode) {

  uint16_t decimal = AF.hi;
  bool carry = readFlag(Flag::C);

  if (!readFlag(Flag::N)) { // Previous operation was addition
    if (readFlag(Flag::H) || (decimal & 0x0F) > 0x09) { // Adjust lower nibble
      decimal += 0x06;
    }
    if (carry || decimal > 0x9F) { // Adjust upper nibble
      decimal += 0x60;
      carry = true;
    }
  } else {                   // Previous operation was subtraction
    if (readFlag(Flag::H)) { // Adjust lower nibble
      decimal = (decimal - 0x06) & 0xFF;
    }
    if (carry) { // Adjust upper nibble
      decimal -= 0x60;
    }
  }

  AF.hi = decimal & 0x00FF;
  writeFlag(Flag::H, 0);
  writeFlag(Flag::Z, AF.hi == 0);
  writeFlag(Flag::C, carry);
}

/*
 * CPL handler
 * Take the compliment of A and store it
 */
void Cpu::handler_CPL(uint8_t opcode) {
  AF.hi = ~AF.hi;
  writeFlag(Flag::N, 1);
  writeFlag(Flag::H, 1);
}
/*
 * Carry flag handler
 * Manages the opcodes related to the carry flag: Set carry flag and clear carry
 * flag (the latter actually just flips it)
 */
void Cpu::handler_XCF(uint8_t opcode) {
  if (opcode == 0x37) {
    writeFlag(Flag::C, 0);
  } else {
    writeFlag(Flag::C, !readFlag(Flag::C));
  }
  writeFlag(Flag::N, 0);
  writeFlag(Flag::H, 0);
}

void Cpu::handler_RET(uint8_t opcode) {
  bool ret = false;
  uint8_t t_states_added = 0;
  switch (opcode) {
  case 0xC0: // RET NZ
    ret = !readFlag(Flag::Z);
    t_states_added = 12;
    break;
  case 0xC8: // RET Z
    ret = readFlag(Flag::Z);
    t_states_added = 12;
    break;
  case 0xC9: // RET
    ret = true;
    t_states_added = 8;
    break;
  case 0xD0: // RET NC
    ret = !readFlag(Flag::C);
    t_states_added = 12;
    break;
  case 0xD8: // RET C
    ret = readFlag(Flag::C);
    t_states_added = 12;
    break;
  }
  if (ret) {
    PC.val = pop16();
    t_states += t_states_added;
  }
}

void Cpu::handler_PUSH(uint8_t opcode) {
  uint16_t *src = decode_reg16_stack_ops(opcode);
  if (src == &AF.val)
    push16(*src & 0xFFF0);
  else
    push16(*src);
}

void Cpu::handler_POP(uint8_t opcode) {
  uint16_t *dst = decode_reg16_stack_ops(opcode);
  *dst = pop16();
  if (dst == &AF.val)
    *dst &= 0xFFF0;
}

/*
 * Disable or enable interupt master enable (IME) flag
 */
void Cpu::handler_DI_EI(uint8_t opcode) {
  if (opcode == 0xF3)
    IME = 0;
  else
    IME_Pending = true;
}

/*
 * STOP opcode handler
 * Stops the internal system clock and oscillator. Has one byte of padding,
 * which is discarded.
 */
void Cpu::handler_STOP(uint8_t opcode) {
  (void)fetch();
  stopped = true;
}

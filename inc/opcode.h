#pragma once

#include <array>
#include <cstdint>

class Cpu;

struct opcode {
  const char *name;
  void (Cpu::*handler)(uint8_t hexVal);
  int t_states;
};

void initOpcodeTable(std::array<opcode, 256> &table);

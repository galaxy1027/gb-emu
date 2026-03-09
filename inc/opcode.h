#pragma once

#include <array>

class Cpu;

struct opcode {
  const char *name;
  void (Cpu::*handler)();
  int t_states;
};

void initOpcodeTable(std::array<opcode, 256> &table);

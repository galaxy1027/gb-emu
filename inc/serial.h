#pragma once

#include <cstdint>

class Serial {
  private:
    uint8_t SB = 0, SC = 0;

  public:
    void write(uint16_t addr, uint8_t val);
    uint8_t read(uint16_t addr);
};
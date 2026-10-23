#pragma once

#include <cstdint>

class Timer {
  private:
    uint16_t DIV;
    uint8_t TIMA;
    uint8_t TMA;
    uint8_t TAC;

  public:
    Timer();
    void init();
    bool tick();

    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t val);
};

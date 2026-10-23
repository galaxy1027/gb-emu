#pragma once

#include "timer.h"
#include <array>
#include <cstdint>
#include <filesystem>

class Bus {
  private:
    std::array<uint8_t, 0x8000> rom{};
    std::array<uint8_t, 0x2000> vram{}, eram{}, wram{};
    std::array<uint8_t, 0xA0> oam{};
    std::array<uint8_t, 0x7F> hram{};
    std::array<uint8_t, 0x80> io{};
    Timer timer;
    uint8_t IF = 0xE1, IE = 0;
    uint8_t readIO(uint16_t addr);
    void writeIO(uint16_t addr, uint8_t val);

  public:
    Bus();
    int loadRom(const std::filesystem::path &path);
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t val);
    void tick(int tCycles);

    void requestInterrupt(int bit);
    void clearInterrupt(int bit);
    uint8_t pendingInterrupts();
};
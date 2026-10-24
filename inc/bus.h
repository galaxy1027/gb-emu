#pragma once

#include "ppu.h"
#include "serial.h"
#include "timer.h"
#include <array>
#include <cstdint>
#include <filesystem>
#include <vector>

struct DMA {
    uint8_t value;
    uint8_t byte;
    uint8_t start_delay;
    bool active = false;
};

class Bus {
  private:
    Timer timer;
    Ppu ppu;
    Serial serial_port;
    DMA dma;
    std::vector<uint8_t> rom{};
    std::array<uint8_t, 0x2000> eram{}, wram{};
    std::array<uint8_t, 0x7F> hram{};
    std::array<uint8_t, 0x80> io{};
    uint8_t IF = 0xE1, IE = 0;
    uint8_t readIO(uint16_t addr);
    void writeIO(uint16_t addr, uint8_t val);
    void startDMA(uint8_t val);
    void tickDMA();

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
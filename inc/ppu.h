#pragma once

#include <array>
#include <cstdint>

typedef struct {
    uint8_t y;
    uint8_t x;
    uint8_t tile;
    uint8_t flags;
} OAM_entry;

enum class OAM_Flag : int {
    PRIORITY = 7,
    Y_FLIP = 6,
    X_FLIP = 5,
    DMG_PALETTE = 4,
    BANK = 3,
    CGB_PALETTE = 0
};

class Ppu {
  private:
    std::array<uint8_t, 0x2000> vram{};
    std::array<uint8_t, 0xA0> oam{};
    std::array<uint32_t, 160 * 144> frameBuffer{};
    uint8_t LY = 0, LYC = 0, STAT = 0x85, LCDC = 0x91, BGP = 0xFC;
    uint8_t SCY = 0, SCX = 0;
    int dot = 0;

    uint8_t readFlagOAM(OAM_entry entry, OAM_Flag f);
    void writeFlagOAM(OAM_entry entry, OAM_Flag f, uint8_t val);

  public:
    Ppu() {};
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t val);
    void init();
    uint8_t tick(int tCycles);
};
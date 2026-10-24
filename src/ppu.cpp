#include "ppu.h"

uint8_t Ppu::read(uint16_t addr) {
    uint8_t read_val = 0xFF;
    if (addr >= 0x8000 && addr <= 0x9FFF) {
        read_val = vram[addr - 0x8000];
    } else if (addr >= 0xFE00 && addr <= 0xFE9F) {
        read_val = oam[addr - 0xFE00];
    } else {
        switch (addr) {
        case 0xFF40:
            read_val = LCDC;
            break;
        case 0xFF41:
            read_val = STAT;
            break;
        case 0xFF42:
            read_val = SCY;
            break;
        case 0xFF43:
            read_val = SCX;
            break;
        case 0xFF44:
            read_val = LY;
            break;
        case 0xFF45:
            read_val = LY;
            break;
        }
    }
    return read_val;
}
void Ppu::write(uint16_t addr, uint8_t val) {
    if (addr >= 0x8000 && addr <= 0x9FFF) {
        vram[addr - 0x8000] = val;
    } else if (addr >= 0xFE00 && addr <= 0xFE9F) {
        oam[addr - 0xFE00] = val;
    } else {
        switch (addr) {
        case 0xFF40:
            LCDC = val;
            break;
        case 0xFF41:
            STAT = val;
            break;
        case 0xFF42:
            SCY = val;
            break;
        case 0xFF43:
            SCX = val;
            break;
        case 0xFF44:
            LY = val;
            break;
        case 0xFF45:
            LY = val;
            break;
        }
    }
}

uint8_t Ppu::readFlagOAM(OAM_entry entry, OAM_Flag f) {
    uint8_t read_val;
    if (f == OAM_Flag::CGB_PALETTE) {
        read_val = entry.flags & ~(0x07);
    } else {
        int bit_pos = static_cast<int>(f);
        read_val = (entry.flags >> bit_pos) & 1;
    }
    return read_val;
}

void Ppu::writeFlagOAM(OAM_entry entry, OAM_Flag f, uint8_t val) {
    uint8_t read_val;
    if (f == OAM_Flag::CGB_PALETTE) {
        entry.flags &= ~(0x07);
        entry.flags |= (val);
    } else {
        int bit_pos = static_cast<int>(f);
        val ? (entry.flags |= 1 << bit_pos) : (entry.flags &= ~(1 << bit_pos));
    }
}

void Ppu::init() {}

uint8_t Ppu::tick(int tCycles) {
    uint8_t irq_vector = 0;
    if ((LCDC & 0x80)) {
        dot += tCycles;
        while (dot >= 456) {
            dot -= 456;
            LY++;
            if (LY == 144)
                irq_vector |= (1 << 0);
            if (LY == 154)
                LY = 0;
        }
    }
    return irq_vector;
}
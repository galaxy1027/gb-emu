#include "bus.h"
#include "cpu.h"
#include <fstream>
#include <iostream>
#include <vector>

Bus::Bus() {}

uint8_t Bus::read(uint16_t addr) {
    uint8_t read_val = 0xFF;
    if (addr < 0x8000)
        read_val = addr < rom.size() ? rom[addr] : 0xFF;
    else if (addr < 0xA000)
        read_val = vram[addr - 0x8000];
    else if (addr < 0xC000)
        read_val = eram[addr - 0xA000];
    else if (addr < 0xE000)
        read_val = wram[addr - 0xC000];
    else if (addr < 0xFE00)
        read_val = wram[addr - 0xE000];
    else if (addr < 0xFEA0)
        read_val = oam[addr - 0xFE00];
    else if (addr < 0xFF00)
        ;
    else if (addr < 0xFF80)
        read_val = readIO(addr);
    else if (addr < 0xFFFF)
        read_val = hram[addr - 0xFF80];
    else
        read_val = IE;
    return read_val;
}

void Bus::write(uint16_t addr, uint8_t val) {
    if (addr < 0x8000)
        ;
    else if (addr < 0xA000)
        vram[addr - 0x8000] = val;
    else if (addr < 0xC000)
        eram[addr - 0xA000] = val;
    else if (addr < 0xE000)
        wram[addr - 0xC000] = val;
    else if (addr < 0xFE00)
        wram[addr - 0xE000] = val;
    else if (addr < 0xFEA0)
        oam[addr - 0xFE00] = val;
    else if (addr < 0xFF00)
        ;
    else if (addr < 0xFF80)
        writeIO(addr, val);
    else if (addr < 0xFFFF)
        hram[addr - 0xFF80] = val;
    else
        IE = val;
}

uint8_t Bus::readIO(uint16_t addr) {
    uint8_t read_val;
    if (addr >= 0xFF04 && addr <= 0xFF07)
        read_val = timer.read(addr);
    else if (addr == 0xFF0F)
        read_val = IF | 0xE0;
    else
        read_val = io[addr - 0xFF00];
    return read_val;
}

void Bus::writeIO(uint16_t addr, uint8_t val) {
    uint8_t read_val;
    if (addr >= 0xFF04 && addr <= 0xFF07)
        timer.write(addr, val);
    else if (addr == 0xFF0F)
        IF = val & 0x1F;

    else if (addr == 0xFF02 &&
             (val & 0x80)) { // Serial port is being written to
        std::cout << (char)io[0x01] << std::flush;
        // Complete transfer
        io[0x01] = 0xFF;
        io[0x02] = val & 0x7F;
    }

    else
        io[addr - 0xFF00] = val;
}

void Bus::tick(int tCycles) {
    for (int i = 0; i < tCycles; i++) {
        if (timer.tick())
            requestInterrupt(2);
    }
}

void Bus::requestInterrupt(int bit) { IF |= (1 << bit); }
void Bus::clearInterrupt(int bit) { IF &= ~(1 << bit); }
void Cpu::serviceInterrupt(uint8_t pending) {
    for (int bit = 0; bit < 5; bit++) {
        if (pending & (1 << bit)) {
            IME = false;
            bus.clearInterrupt(bit);
            push16(PC.val);
            PC.val = 0x40 + bit * 8;
            t_cycles += 20;
            return;
        }
    }
}

uint8_t Bus::pendingInterrupts() { return IE & IF & 0x1F; }

int Bus::loadRom(const std::filesystem::path &filePath) {
    int loaded = 0;
    std::ifstream file(filePath, std::ios::binary);
    if (!file || filePath.extension() != ".gb") {
        std::cerr << "Error: Attempted to load invalid ROM!\n";
        loaded = 1;
    } else {
        std::vector<uint8_t> loaded_file((std::istreambuf_iterator<char>(file)),
                                         std::istreambuf_iterator<char>());
        for (size_t i = 0; i < loaded_file.size() && i < 0x8000; i++) {
            rom[i] = loaded_file[i];
        }
        std::cout << "Rom Loaded\n";
    }
    file.close();
    return loaded;
}
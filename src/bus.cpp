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
        read_val = ppu.read(addr);
    else if (addr < 0xC000)
        read_val = eram[addr - 0xA000];
    else if (addr < 0xE000)
        read_val = wram[addr - 0xC000];
    else if (addr < 0xFE00)
        read_val = wram[addr - 0xE000];
    else if (addr < 0xFEA0)
        read_val = ppu.read(addr);
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
        ppu.write(addr, val);
    else if (addr < 0xC000)
        eram[addr - 0xA000] = val;
    else if (addr < 0xE000)
        wram[addr - 0xC000] = val;
    else if (addr < 0xFE00)
        wram[addr - 0xE000] = val;
    else if (addr < 0xFEA0)
        ppu.write(addr, val);
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
    if (addr >= 0xFF04 && addr <= 0xFF07) // Timer IO
        read_val = timer.read(addr);
    else if (addr == 0xFF0F) // Interrupt flag IO
        read_val = IF | 0xE0;
    else if (addr >= 0xFF40 && addr <= 0xFF4B && addr != 0xFF46) // PPU IO
        read_val = ppu.read(addr);
    else if (addr == 0xFF46)
        read_val = 0xFF;
    else if (addr == 0xFF01 || addr == 0xFF02) // Serial port IO
        read_val = serial_port.read(addr);
    else
        read_val = io[addr - 0xFF00];
    return read_val;
}

void Bus::writeIO(uint16_t addr, uint8_t val) {
    uint8_t read_val;
    if (addr >= 0xFF04 && addr <= 0xFF07) // Timer IO
        timer.write(addr, val);
    else if (addr == 0xFF0F) // Interrupt flag IO
        IF = val & 0x1F;
    else if (addr >= 0xFF40 && addr <= 0xFF4B && addr != 0xFF46) // PPU IO
        ppu.write(addr, val);
    else if (addr == 0xFF46) // DMA
        startDMA(val);

    else if (addr == 0xFF01 || addr == 0xFF02) { // Serial port
        serial_port.write(addr, val);
        if (addr == 0xFF02 && (val & 0x80))
            requestInterrupt(3);
    } else
        io[addr - 0xFF00] = val; // Generic IO fallback functionality
}

void Bus::tick(int tCycles) {
    uint8_t IRQ_Vector = 0;
    for (int i = 0; i < tCycles; i++) {
        IRQ_Vector |= timer.tick();
        if (i % 4 == 0)
            tickDMA();
    }
    IRQ_Vector |= ppu.tick(tCycles);

    IF |= IRQ_Vector;
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

void Bus::startDMA(uint8_t val) {
    dma.active = true;
    dma.start_delay = 2;
    dma.value = val;
    dma.byte = 0;
}

void Bus::tickDMA() {
    if (dma.active) {
        if (dma.start_delay)
            dma.start_delay--;
        else {
            ppu.write(dma.byte, read(dma.value) * 0x100 + dma.byte);
            dma.byte++;
            dma.active = dma.byte < 0xA0;
        }
    }
}
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
            rom.push_back(loaded_file[i]);
        }
        std::cout << "Rom Loaded\n";
    }
    file.close();
    return loaded;
}
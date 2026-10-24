#include "serial.h"
#include <iostream>

void Serial::write(uint16_t addr, uint8_t val) {
    if (addr == 0xFF01) {
        SB = val;
    } else if (addr == 0xFF02) {
        SC = val;
        if (val & 0x80) {
            std::cout << (char)SB << std::flush;
            SC &= 0x7F;
        }
    }
}

uint8_t Serial::read(uint16_t addr) {
    uint8_t read_val;
    if (addr == 0xFF01) {
        read_val = SB;
    } else if (addr == 0xFF02) {
        read_val = SC | 0x7E;
    }
    return read_val;
}

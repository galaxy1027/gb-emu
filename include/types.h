#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef uint8_t byte;

const uint16_t cartridge_base_addr = 0x00;
const uint16_t vram_base_addr = 0x8000;
const uint16_t wram_base_addr = 0xC000;

#endif

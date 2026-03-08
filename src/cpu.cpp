#include "cpu.h"
cpuZ80::cpuZ80() {
    memory = std::array<uint8_t, 0x10000>();
}

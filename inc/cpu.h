#pragma once

#include <array>
#include <cstdint>

struct cpu_reg {
    union {
        struct {
            uint8_t lo;
            uint8_t hi;
        };
        uint16_t val;
    };
};

class cpuZ80 {
    private:
    cpu_reg AF, BC, DE, HL;
    uint16_t SP, PC;
    bool IME;
    std::array<uint8_t, 10000> memory;

    cpuZ80();
};

#include "timer.h"

Timer::Timer() { init(); }

void Timer::init() {
    DIV = 0xAC00;
    TIMA = TMA = TAC = 0;
}

/* Timer Tick
 *  Returns a value of true if an interrupt is requested.
 * */
bool Timer::tick() {
    bool request_interrupt = false;
    uint16_t prev_div = DIV;
    DIV++;
    bool timer_update = false;

    /* Change how fast the timer increments based on the TAC bottom 2 bits. This
     * is changed by incrementing specific bit positions in the DIV register */
    switch (TAC & (0b11)) {
    case 0b00:
        timer_update = (prev_div & (1 << 9)) && (!(DIV & (1 << 9)));
        break;
    case 0b01:
        timer_update = (prev_div & (1 << 3)) && (!(DIV & (1 << 3)));
        break;
    case 0b10:
        timer_update = (prev_div & (1 << 5)) && (!(DIV & (1 << 5)));
        break;
    case 0b11:
        timer_update = (prev_div & (1 << 7)) && (!(DIV & (1 << 7)));
        break;
    }
    // increment the TIMA register if the TAC enable bit is set
    if (timer_update && (TAC & (1 << 2))) {
        TIMA++;
        if (TIMA == 0x00) {
            TIMA = TMA;
            request_interrupt = true;
        }
    }
    return request_interrupt;
}

uint8_t Timer::read(uint16_t addr) {
    uint8_t read_val = 0;
    switch (addr) {
    case 0xFF04: // DIV
        read_val = DIV >> 8;
        break;
    case 0xFF05:
        read_val = TIMA;
        break;
    case 0xFF06:
        read_val = TMA;
        break;
    case 0xFF07:
        read_val = TAC;
        break;
    }
    return read_val;
}

void Timer::write(uint16_t addr, uint8_t val) {
    switch (addr) {
    case 0xFF04: // DIV
        DIV = 0;
        break;
    case 0xFF05:
        TIMA = val;
        break;
    case 0xFF06:
        TMA = val;
        break;
    case 0xFF07:
        TAC = val;
        break;
    }
}

#include "gb.hpp"

int main() {
    GameBoy *emu = new GameBoy();
    while (1) {
        emu->Fetch();
        emu->Execute();
    }
    delete(emu);
}

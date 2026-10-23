#pragma once

#include "bus.h"
#include "opcode.h"
#include <array>
#include <cstdint>
#include <filesystem>

/*
 * Flag values indicate bit position in the F register
 * Lower nibble of register is unused
 *  HI   LO
 * ZNHC XXXX
 */
enum class Flag : int { Z = 7, N = 6, H = 5, C = 4 };

/*
 * Reg16 - a 16 bit register
 * Actually a pair of 2 8-bit registers.
 *
 * For each register, the respective low and high bytes of each pair are:
 * lo   hi
 * A    F
 * B    C
 * D    E
 * H    L
 */
struct Reg16 {
    union {
        struct {
            uint8_t lo;
            uint8_t hi;
        };
        uint16_t val;
    };
};

class Cpu {
  private:
    Reg16 AF, BC, DE, HL, SP, PC;
    bool IME, IME_Pending, stopped, halted;
    int t_cycles;
    std::array<opcode, 256> opcodeTable;
    uint8_t opcodeFetched;

    Bus &bus;

    /* Private helper functions */

    uint8_t fetch();
    uint16_t fetch16();
    void execute();

    uint8_t readReg8(uint8_t opcode, char type);
    void writeReg8(uint8_t opcode, uint8_t val);
    void writeReg8(uint8_t opcode, char type, uint8_t val);

    uint8_t *getMemoryPtr(uint16_t address);
    void store8(uint8_t data, uint16_t address);
    void store16(uint16_t data, uint16_t address);
    uint8_t read8(uint16_t addr);
    uint16_t read16(uint16_t addr);
    void writeFlag(Flag F, bool value);
    bool readFlag(Flag F);
    void load8(uint16_t addr, uint8_t &dest);
    void loadReg16(uint16_t addr, Reg16 &dest);
    void incReg16(Reg16 &reg);
    void decReg16(Reg16 &reg);
    void addReg16(uint16_t &source, uint16_t &dest);
    void addSetH(uint8_t a, uint8_t b);
    void add16SetH(uint16_t a, uint16_t b);
    void subSetH(uint8_t a, uint8_t b);
    void rotateLeftCarry(uint8_t &reg);
    void rotateRightCarry(uint8_t &reg);
    void rotateLeft(uint8_t &reg);
    void rotateRight(uint8_t &reg);
    void shiftLeftArithmetic(uint8_t &reg);
    void shiftRightArithmetic(uint8_t &reg);
    void shiftRightLogical(uint8_t &reg);
    void swapNibbles(uint8_t &reg);
    void copyBit(uint8_t &reg, int bitPos);
    void resetBit(uint8_t &reg, int bitPos);
    void setBit(uint8_t &reg, int bitPos);
    uint8_t pop();
    uint16_t pop16();
    void push(uint8_t val);
    void push16(uint16_t val);

    uint8_t *decode_reg8(uint8_t opcode, char type);
    uint8_t *decode_reg8(uint8_t opcode);
    uint16_t *decode_reg16(uint8_t opcode);
    uint16_t *decode_reg16_stack_ops(uint8_t opcode);

    /* Interrupt */
    void requestInterrupt(int bit);
    void serviceInterrupt(uint8_t pending);

    /* Opcode handlers */

    void handler_NOP(uint8_t opcode);
    void handler_LD_r8_d8(uint8_t opcode);
    void handler_LD_r16_d16(uint8_t opcode);
    void handler_LD_r8_r8(uint8_t opcode);
    void handler_LD_mem_A(uint8_t opcode);
    void handler_LD_A_mem(uint8_t opcode);
    void handler_LD_mem_SP(uint8_t opcode);
    void handler_LD_a16(uint8_t opcode);
    void handler_LD_a8(uint8_t opcode);
    void handler_INC_DEC_r8(uint8_t opcode);
    void handler_INC_DEC_r16(uint8_t opcode);
    void handler_ADD_HL_r16(uint8_t opcode);
    void handler_ADD_r8_r8(uint8_t opcode);
    void handler_ADC_r8_r8(uint8_t opcode);
    void handler_SUB_r8(uint8_t opcode);
    void handler_SBC_r8_r8(uint8_t opcode);
    void handler_AND_r8(uint8_t opcode);
    void handler_XOR_r8(uint8_t opcode);
    void handler_OR_r8(uint8_t opcode);
    void handler_CP_r8(uint8_t opcode);
    void handler_ADD_r8_d8(uint8_t opcode);
    void handler_ADC_r8_d8(uint8_t opcode);
    void handler_SUB_d8(uint8_t opcode);
    void handler_SBC_r8_d8(uint8_t opcode);
    void handler_AND_d8(uint8_t opcode);
    void handler_XOR_d8(uint8_t opcode);
    void handler_OR_d8(uint8_t opcode);
    void handler_CP_d8(uint8_t opcode);
    void handler_JR_s8(uint8_t opcode);
    void handler_RRC_r8(uint8_t opcode);
    void handler_RLC_r8(uint8_t opcode);
    void handler_RR_r8(uint8_t opcode);
    void handler_RL_r8(uint8_t opcode);
    void handler_DAA(uint8_t opcode);
    void handler_CPL(uint8_t opcode);
    void handler_XCF(uint8_t opcode);
    void handler_RET(uint8_t opcode);
    void handler_PUSH(uint8_t opcode);
    void handler_POP(uint8_t opcode);
    void handler_LD_HL_SP_s8(uint8_t opcode);
    void handler_LD_SP_HL(uint8_t opcode);
    void handler_JP_a16(uint8_t opcode);
    void handler_JP_HL(uint8_t opcode);
    void handler_CALL_a16(uint8_t opcode);
    void handler_DI_EI(uint8_t opcode);
    void handler_RETI(uint8_t opcode);
    void handler_RST(uint8_t opcode);
    void handler_STOP(uint8_t opcode);
    void handler_HALT(uint8_t opcode);
    void handler_CB_PREFIX(uint8_t opcode);

    /* CB prefixed helpers */
    void CB_RLC_r8(uint8_t &val);
    void CB_RRC_r8(uint8_t &val);
    void CB_RR_r8(uint8_t &val);
    void CB_RL_r8(uint8_t &val);
    void CB_SLA_r8(uint8_t &val);
    void CB_SRA_r8(uint8_t &val);
    void CB_SWAP_r8(uint8_t &val);
    void CB_SRL_r8(uint8_t &val);
    void BIT_n_r8(uint8_t &val, uint8_t bit);
    void RES_n_r8(uint8_t &val, uint8_t bit);
    void SET_n_r8(uint8_t &val, uint8_t bit);
    void initOpcodeTable();

  public:
    explicit Cpu(Bus &b) : bus(b) {
        PC.val = 0x1000;
        initOpcodeTable();
        AF.val = (0x01B0);
        BC.val = (0x0013);
        DE.val = (0x00D8);
        HL.val = (0x014D);

        SP.val = (0xFFFE);
        PC.val = (0x0100);

        halted = false;
        stopped = false;
        IME = false;
        IME_Pending = false;
    };

    int loadRom(const std::filesystem::path &filePath);
    int step();
    void writeByteMemory(uint16_t address, uint8_t data);
    uint8_t readByteMemory(uint16_t addr);
    uint8_t timerReadByte(uint16_t addr);
    void timerWriteByte(uint16_t addr, uint8_t val);

    void printRegs();
    void printDebug();
};

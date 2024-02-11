#include "Instruction.h"

// Function to create an instruction
uint32_t createInstruction(Opcode opcode, FPRegister dst, FPRegister src0, FPRegister src1) {
    uint32_t instruction = 0; // Start with an empty instruction
    instruction |= ((uint32_t)opcode << OPCODE_SHIFT) & OPCODE_MASK;
    instruction |= ((uint32_t)dst << DST_SHIFT) & DST_MASK;
    instruction |= ((uint32_t)src0 << SRC0_SHIFT) & SRC0_MASK;
    instruction |= ((uint32_t)src1 << SRC1_SHIFT) & SRC1_MASK;
    return instruction;
}

// Functions to extract fields from an instruction
Opcode getOpcode(uint32_t instruction) {
    return (Opcode)((instruction & OPCODE_MASK) >> OPCODE_SHIFT);
}

FPRegister getDst(uint32_t instruction) {
    return (FPRegister)((instruction & DST_MASK) >> DST_SHIFT);
}

FPRegister getSrc0(uint32_t instruction) {
    return (FPRegister)((instruction & SRC0_MASK) >> SRC0_SHIFT);
}

FPRegister getSrc1(uint32_t instruction) {
    return (FPRegister)((instruction & SRC1_MASK) >> SRC1_SHIFT);
}

// Function to print register name
void printRegisterName(FPRegister reg) {
    printf("F%d", reg);
}



#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Registers.h"

// Enum for opcodes
typedef enum {
    ADD = 2,
    SUB = 3,
    MULT = 4,
    DIV = 5,
    HALT = 6
} Opcode;

// Define masks and shifts according to the instruction layout
#define OPCODE_SHIFT 24
#define DST_SHIFT    20
#define SRC0_SHIFT   16
#define SRC1_SHIFT   12
#define OPCODE_MASK  0xF0000000
#define DST_MASK     0x00F00000
#define SRC0_MASK    0x000F0000
#define SRC1_MASK    0x0000F000

// Instruction struct
typedef struct {
    Opcode opcode;
    FPRegister dst;
    FPRegister src0;
    FPRegister src1;
} Instruction;

// Function declarations
Opcode getOpcode(uint32_t instruction);
FPRegister getDst(uint32_t instruction);
FPRegister getSrc0(uint32_t instruction);
FPRegister getSrc1(uint32_t instruction);


Instruction* createInstruction(uint32_t hexInstruction);
void freeInstruction(Instruction* instr);
void printInstruction(const Instruction* instr);
Instruction* get_next_instruction(FILE* memin);
void printInstructionsFromFile(const char* filename);

#endif // INSTRUCTION_H

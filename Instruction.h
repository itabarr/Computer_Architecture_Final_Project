#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "globals.h"

// Instruction struct
typedef struct {
    Opcode opcode;
    FPRegister dst;
    FPRegister src0;
    FPRegister src1;

    // Instruction metadata for printing / debugging
    uint32_t PC;
    uint32_t Issue;
    uint32_t Execute;
    uint32_t Write_CDB;

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

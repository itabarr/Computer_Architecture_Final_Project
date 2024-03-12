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
    uint32_t instruction_hex;
    ReservationStationTag tag;
    uint32_t Issue;
    uint32_t Execute_Start;
    uint32_t Execute_End;
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
Instruction* get_next_instruction(FILE* memin, Instruction** inst_table);
void printInstructionsFromFile(const char* filename);
Instruction** allocateInstructionPointerTable();
void freeInstructionPointerTable(Instruction** instructionTable);
void printInstructionTable(Instruction** instructionTable);
#endif // INSTRUCTION_H

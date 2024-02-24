#include "Instruction.h"

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

// Instruction struct functionallity
Instruction* createInstruction(uint32_t hexInstruction) {
    Instruction* instr = (Instruction*)malloc(sizeof(Instruction));
    if (instr == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    // Decode the instruction
    instr->opcode = getOpcode(hexInstruction);
    instr->dst = getDst(hexInstruction);
    instr->src0 = getSrc0(hexInstruction);
    instr->src1 = getSrc1(hexInstruction);
    return instr;
}
void freeInstruction(Instruction* instr) {
    free(instr);
}
void printInstruction(const Instruction* instr) {
    printf("Opcode: %d, DST: ", instr->opcode);
    printRegisterName(instr->dst);
    printf(", SRC0: ");
    printRegisterName(instr->src0);
    printf(", SRC1: ");
    printRegisterName(instr->src1);
    printf("\n");
}
Instruction* get_next_instruction(FILE* memin) {
    uint32_t hexInstruction;
    char line[9]; 

    if (fgets(line, sizeof(line), memin) == NULL) {
        return NULL; 
    }

    if (sscanf_s(line, "%x", &hexInstruction) != 1) {
        return NULL; 
    }

    Instruction* instr = createInstruction(hexInstruction);
    return instr;
}
void printInstructionsFromFile(const char* filename) {
    FILE* memin = fopen(filename, "r");
    if (!memin) {
        perror("Failed to open file for reading");
        return;
    }

    Instruction* instr;
    while ((instr = get_next_instruction(memin)) != NULL) {
        printInstruction(instr);
        freeInstruction(instr); 
    }

    fclose(memin);
}


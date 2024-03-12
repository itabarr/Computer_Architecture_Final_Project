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
    instr->PC = INST_COUNTER;
    instr->instruction_hex = hexInstruction;

    instr->Issue = 0;
    instr->Execute_Start = 0;
    instr->Execute_End = 0;
    instr->Write_CDB = 0;

    INST_COUNTER++;
    return instr;
}
void freeInstruction(Instruction* instr) {
    free(instr);
}
void printInstruction(const Instruction* instr) {
    printf("%08x %u ", instr->instruction_hex, instr->PC);

    if (instr->tag.ResType == OP_ADD) {
        printf("ADD%d ", instr->tag.ResIndex - 1);
    }
    else if (instr->tag.ResType == OP_MUL) {
        printf("MUL%d ", instr->tag.ResIndex - 1);
    }
    else if (instr->tag.ResType == OP_DIV) {
        printf("DIV%d ", instr->tag.ResIndex - 1);
    }
    else {
        printf("UNKNOWN ");
    }

    printf("%u %u %u %u\n", instr->Issue, instr->Execute_Start, instr->Execute_End, instr->Write_CDB);
}
Instruction* get_next_instruction(FILE* memin , Instruction** inst_table) {
    uint32_t hexInstruction;
    char line[10]; 

    if (fgets(line, sizeof(line), memin) == NULL) {
        
        return NULL; 
    }

    line[8] = '\0';
    if (sscanf_s(line, "%x", &hexInstruction) != 1) {
        return NULL; 
    }

    Instruction* instr = createInstruction(hexInstruction);
    inst_table[instr->PC] = instr;

    return instr;
}
void printInstructionsFromFile(const char* filename) {
    FILE* memin = fopen(filename, "r");
    if (!memin) {
        perror("Failed to open file for reading");
        return;
    }

    Instruction* instr;
    /*while ((instr = get_next_instruction(memin ,inst_table)) != NULL) {
        printInstruction(instr);
        freeInstruction(instr); 
    }*/

    fclose(memin);
}
Instruction** allocateInstructionPointerTable() {
    Instruction** instructionTable = (Instruction**)malloc(INST_NUM * sizeof(Instruction*));
    if (instructionTable == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    // Initialize all pointers to NULL
    for (int i = 0; i < INST_NUM; ++i) {
        instructionTable[i] = NULL;
    }

    return instructionTable;
}
void freeInstructionPointerTable(Instruction** instructionTable) {
    if (instructionTable == NULL) {
        return;
    }

    // Free each allocated Instruction structure
    for (int i = 0; i < INST_NUM; ++i) {
        if (instructionTable[i] != NULL) {
            freeInstruction(instructionTable[i]);
        }
    }

    // Free the instruction table itself
    free(instructionTable);
}
void printInstructionTable(Instruction** instructionTable) {
    if (instructionTable == NULL) {
        printf("Instruction table is NULL\n");
        return;
    }

    printf("Instruction Table:\n");
    for (int i = 0; i < INST_NUM; ++i) {
        if (instructionTable[i] != NULL) {
            printInstruction(instructionTable[i]);
        }
    }
}
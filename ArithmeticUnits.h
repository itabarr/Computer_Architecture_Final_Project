// unit_operations.h
#ifndef UNIT_OPERATIONS_H
#define UNIT_OPERATIONS_H

#include "config.h" 
#include "Instruction.h"

// Enum for opcodes
typedef enum {
    OP_ADD = 0,
    OP_MUL = 1,
    OP_DIV = 2,
} Operation;

typedef struct {
    Operation operation;
    float operand1;
    float operand2;
    float result;
    int inner_delay;
    int ready;
    int sign;
} Unit;

Unit* UNIT_ARRAY;

// Function prototypes
void initUnit(Unit* unit, Operation operation);
void insertOperands(Unit* unit, float operand1, float operand2);
void executeOperation(Unit* unit);

#endif // UNIT_OPERATIONS_H


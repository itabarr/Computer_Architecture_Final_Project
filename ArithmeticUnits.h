// unit_operations.h
#ifndef UNIT_OPERATIONS_H
#define UNIT_OPERATIONS_H

#include "globals.h"
#include "Instruction.h"

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


#include "ArithmeticUnits.h"

void initUnit(Unit* unit, Operation operation){
    unit->operation = operation;
    unit->operand1 = 0.0f;
    unit->operand2 = 0.0f;
    unit->result = 0.0f;
    unit->inner_delay = 0;
    unit->ready = 0;
    unit->sign = 0;
}
void insertOperands(Unit* unit , float operand1, float operand2) {
    unit->operand1 = operand1;
    unit->operand2 = operand2;
}
void executeOperation(Unit* unit) {
    // Check if the operation is ready to be executed
    if (unit->inner_delay < 0) {
        printf("Operation not initialized properly.\n");
        return;
    }

    switch (unit->operation) {
    case OP_ADD:
        if (unit->inner_delay == ADD_DELAY - 1) {
            if (unit->sign == 0) {
                unit->result = unit->operand1 + unit->operand2;
                unit->ready = 1;
            }
            else {
                unit->result = unit->operand1 - unit->operand2;
                unit->ready = 1;
            } 
        }
        break;
    case OP_MUL:
        if (unit->inner_delay == MUL_DELAY - 1) {
            unit->result = unit->operand1 * unit->operand2;
            unit->ready = 1;
        }
        break;
    case OP_DIV:
        if (unit->inner_delay == DIV_DELAY - 1) {
            if (unit->operand2 != 0) {
                unit->result = unit->operand1 / unit->operand2;
                unit->ready = 1;
            }
            else {
                printf("Error: Division by zero.\n");
                unit->ready = -1; // Indicate error
            }
        }
        break;
    default:
        printf("Unsupported operation.\n");
        return;
    }
    // Increment inner_delay if not ready
    if (!unit->ready) {
        unit->inner_delay++;
    }
    else {
        // Reset inner_delay for potential reuse
        unit->inner_delay = 0;
    }
}


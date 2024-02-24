// unit_operations.h
#ifndef UNIT_OPERATIONS_H
#define UNIT_OPERATIONS_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "globals.h"
#include "Instruction.h"

typedef struct {
    uint32_t IsBusy;
    uint32_t InternalTimer;
    
} Unit;

typedef struct {
    Unit* AddUnits;
    Unit* MulUnits;
    Unit* DivUnits;

    uint32_t ADD_size;
    uint32_t MUL_size;
    uint32_t DIV_size;

} UnitArray;


UnitArray* createUnitArray(void);
void freeUnitArray(UnitArray* ua);

#endif // UNIT_OPERATIONS_H


// MemoryAllocation.c
#include "MemoryAllocation.h"
#include "ArithmeticUnits.h"
#include <stdlib.h> // For malloc and free

Unit* allocateUnitArray(void) {
    int UNIT_ARRAY_SIZE = ADD_NR_UNITS + MUL_NR_UNITS + DIV_NR_UNITS;
    // Allocate memory for an array of unit_data structures
    Unit* ALOC_UNIT_ARRAY = (Unit*)malloc(UNIT_ARRAY_SIZE * sizeof(Unit));
    if (ALOC_UNIT_ARRAY == NULL) {
        // Handle memory allocation failure if needed
        return NULL;
    }

    // Optionally initialize the allocated array
    for (int i = 0; i < ADD_NR_UNITS; ++i) {
        initUnit(&ALOC_UNIT_ARRAY[i], OP_ADD); // Example initialization, adjust as needed
    }

    for (int i = 0; i < MUL_NR_UNITS; ++i) {
        initUnit(&ALOC_UNIT_ARRAY[i + ADD_NR_UNITS], OP_MUL); // Example initialization, adjust as needed
    }

    for (int i = 0; i < DIV_NR_UNITS; ++i) {
        initUnit(&ALOC_UNIT_ARRAY[i + ADD_NR_UNITS + MUL_NR_UNITS], OP_DIV); // Example initialization, adjust as needed
    }
    
    return ALOC_UNIT_ARRAY;
}

void freeUnitArray(Unit* array) {
    // Free the allocated memory
    free(array);
}
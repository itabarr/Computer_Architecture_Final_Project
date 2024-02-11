// MemoryAllocation.h
#ifndef MEMORY_ALLOCATION_H
#define MEMORY_ALLOCATION_H

#include "ArithmeticUnits.h" // For unit_data struct
#include "config.h" // For UNIT_ARRAY_SIZE

// Function prototypes
Unit* allocateUnitArray(void);
void freeUnitArray(Unit* UnitArray);

#endif // MEMORY_ALLOCATION_H

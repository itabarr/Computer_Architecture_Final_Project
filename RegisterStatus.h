#ifndef REGISTERSTATUS_H
#define REGISTERSTATUS_H

#include "globals.h"

typedef struct {
    float Vi[NUM_REGISTERS]; // Array to store the register values
    ReservationStationTag Qi[NUM_REGISTERS];
    uint32_t QiValid[NUM_REGISTERS];
} RegistersTable;

// Function prototype to initialize the registers table
void initRegistersTable(RegistersTable* rt);
void outputRegistersToFile(const RegistersTable* rt, const char* filePath);
void printRegisterName(FPRegister reg);

#endif
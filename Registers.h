#ifndef REGISTERS_H
#define REGISTERS_H

#define NUM_REGISTERS 16
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "ReservationStation.h"

// Enum for floating-point registers F0-F15
typedef enum {
    F0, F1, F2, F3, F4, F5, F6, F7,
    F8, F9, F10, F11, F12, F13, F14, F15
} FPRegister;

typedef struct {
    float Vi[NUM_REGISTERS]; // Array to store the register values
    ReservationStationTag Qi[NUM_REGISTERS];
    int QiValid;
} RegistersTable;

// Function prototype to initialize the registers table
void initRegistersTable(RegistersTable* rt);
void outputRegistersToFile(const RegistersTable* rt, const char* filePath);
void printRegisterName(FPRegister reg);

#endif // REGISTERS_H

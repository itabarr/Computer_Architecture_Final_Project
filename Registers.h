#ifndef REGISTERS_H
#define REGISTERS_H

#define NUM_REGISTERS 16

// Enum for floating-point registers F0-F15
typedef enum {
    F0, F1, F2, F3, F4, F5, F6, F7,
    F8, F9, F10, F11, F12, F13, F14, F15
} FPRegister;

typedef struct {
    float registers[NUM_REGISTERS]; // Array to store the register values
} RegistersTable;

// Function prototype to initialize the registers table
void initRegistersTable(RegistersTable* rt);
void outputRegistersToFile(const RegistersTable* rt, const char* filePath);

#endif // REGISTERS_H

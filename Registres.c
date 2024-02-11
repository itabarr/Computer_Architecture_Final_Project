// Registers.c

#include "Registers.h"
#include <stdio.h>

// Initialize the registers table
void initRegistersTable(RegistersTable* rt) {
    for (int i = 0; i < NUM_REGISTERS; i++) {
        rt->registers[i] = (float)i; // Initialize each register to it's index
    }
}

void outputRegistersToFile(const RegistersTable* rt, const char* filePath) {
    FILE* file = fopen(filePath, "w"); // Open the file for writing
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    for (int i = 0; i < NUM_REGISTERS; i++) {
        fprintf(file, "F%d = %.1f\n", i, rt->registers[i]); // Write each register to the file
    }

    fclose(file); // Close the file
}
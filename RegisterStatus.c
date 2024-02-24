// Registers.c

#include "globals.h"
#include "RegisterStatus.h"
#include <stdio.h>

// Initialize the registers table
void initRegistersTable(RegistersTable* rt) {
    for (int i = 0; i < NUM_REGISTERS; i++) {
        rt->Vi[i] = (float)i; // Initialize each register to it's index
        rt->QiValid[i] = 0;
    }

}

void outputRegistersToFile(const RegistersTable* rt, const char* filePath) {
    FILE* file = fopen(filePath, "w"); // Open the file for writing
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    for (int i = 0; i < NUM_REGISTERS; i++) {
        fprintf(file, "F%d = %.1f\n", i, rt->Vi[i]); // Write each register to the file
    }

    fclose(file); // Close the file
}

void printRegisterName(FPRegister reg) {
    printf("F%d", reg);
}
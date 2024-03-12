#include "globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


uint32_t ADD_NR_UNITS = 2;
uint32_t MUL_NR_UNITS = 1;
uint32_t DIV_NR_UNITS = 1;
uint32_t ADD_NR_RESERVATION = 2;
uint32_t MUL_NR_RESERVATION = 2;
uint32_t DIV_NR_RESERVATION = 2;
uint32_t ADD_DELAY = 2;
uint32_t MUL_DELAY = 5;
uint32_t DIV_DELAY = 20;
uint32_t CLK = 0;
uint32_t INST_NUM = 0;
uint32_t INST_COUNTER = 0;


void read_config_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }
        
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, "=");
        remove_end_spaces(token);

        char* valueStr = strtok(NULL, "\n");

        if (token && valueStr) {
            int value = atoi(valueStr);

            if (strcmp(token, "add_nr_units") == 0) ADD_NR_UNITS = value;
            else if (strcmp(token, "mul_nr_units") == 0) MUL_NR_UNITS = value;
            else if (strcmp(token, "div_nr_units") == 0) DIV_NR_UNITS = value;
            else if (strcmp(token, "add_nr_reservation") == 0) ADD_NR_RESERVATION = value;
            else if (strcmp(token, "mul_nr_reservation") == 0) MUL_NR_RESERVATION = value;
            else if (strcmp(token, "div_nr_reservation") == 0) DIV_NR_RESERVATION = value;
            else if (strcmp(token, "add_delay") == 0) ADD_DELAY = value;
            else if (strcmp(token, "mul_delay") == 0) MUL_DELAY = value;
            else if (strcmp(token, "div_delay") == 0) DIV_DELAY = value;
        }
    }

    fclose(file);
}

void remove_end_spaces(char* str) {
    size_t index;
    index = strlen(str) - 1;
    while (index >= 0 && (str[index] == ' ' || str[index] == '\t')) {
        index--;
    }
    str[index + 1] = '\0';
}

int count_lines_in_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open file: %s\n", filename);
        return -1; // Return -1 to indicate an error occurred while opening the file
    }

    int line_count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            line_count++;
        }
    }

    fclose(file);
    INST_NUM = line_count;
    return line_count;
}
//This is Roi the king!mbmn
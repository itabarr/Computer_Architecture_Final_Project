#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int ADD_NR_UNITS = 2;
int MUL_NR_UNITS = 1;
int DIV_NR_UNITS = 1;
int ADD_NR_RESERVATION = 2;
int MUL_NR_RESERVATION = 2;
int DIV_NR_RESERVATION = 2;
int ADD_DELAY = 2;
int MUL_DELAY = 5;
int DIV_DELAY = 20;

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
    int index, i;
    index = strlen(str) - 1;
    while (index >= 0 && (str[index] == ' ' || str[index] == '\t')) {
        index--;
    }
    str[index + 1] = '\0';
}
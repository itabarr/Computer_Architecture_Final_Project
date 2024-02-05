#pragma once

// Declare external config-global variables
extern int ADD_NR_UNITS;
extern int MUL_NR_UNITS;
extern int DIV_NR_UNITS;
extern int ADD_NR_RESERVATION;
extern int MUL_NR_RESERVATION;
extern int DIV_NR_RESERVATION;
extern int ADD_DELAY;
extern int MUL_DELAY;
extern int DIV_DELAY;

// Function declaration to update config from a file
void read_config_from_file(const char* filename);
void remove_end_spaces(char* str);


#ifndef GLOBALS_H
#define GLOBALS_H

#define NUM_REGISTERS 16
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdint.h>

// Declare external config-global variables
extern uint32_t ADD_NR_UNITS;
extern uint32_t MUL_NR_UNITS;
extern uint32_t DIV_NR_UNITS;
extern uint32_t ADD_NR_RESERVATION;
extern uint32_t MUL_NR_RESERVATION;
extern uint32_t DIV_NR_RESERVATION;
extern uint32_t ADD_DELAY;
extern uint32_t MUL_DELAY;
extern uint32_t DIV_DELAY;

// Define masks and shifts according to the instruction layout
#define OPCODE_SHIFT 24
#define DST_SHIFT    20
#define SRC0_SHIFT   16
#define SRC1_SHIFT   12
#define OPCODE_MASK  0x0F000000
#define DST_MASK     0x00F00000
#define SRC0_MASK    0x000F0000
#define SRC1_MASK    0x0000F000

#define QUEUE_SIZE 16

typedef enum {
    F0, F1, F2, F3, F4, F5, F6, F7,
    F8, F9, F10, F11, F12, F13, F14, F15
} FPRegister;

// Enum for opcodes
typedef enum {
    ADD = 2,
    SUB = 3,
    MULT = 4,
    DIV = 5,
    HALT = 6
} Opcode;

// Enum for opcodes
typedef enum {
    OP_ADD = 0,
    OP_MUL = 1,
    OP_DIV = 2,
} Operation;

typedef struct {
    enum Operation ResType;
    uint32_t ResIndex;
} ReservationStationTag;


// Function declaration to update config from a file
void read_config_from_file(const char* filename);
void remove_end_spaces(char* str);

#endif
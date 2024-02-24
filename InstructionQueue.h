#ifndef INSTRUCTION_QUEUE_H
#define INSTRUCTION_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "Instruction.h"

#define QUEUE_SIZE 16

// Structure to represent the instruction queue
typedef struct {
    Instruction* buffer[QUEUE_SIZE]; // Array to store pointers to the instructions
    int head;                        // Points to the start of the queue
    int tail;                        // Points to the end of the queue
    int count;                       // Number of items in the queue
} InstructionQueue;

// Function prototypes
void initQueue(InstructionQueue* q);
int isFull(InstructionQueue* q);
int isEmpty(InstructionQueue* q);
int enqueue(InstructionQueue* q, Instruction* instruction); 
int dequeue(InstructionQueue* q, Instruction** instruction); 


// Function prototypes for dynamic allocation and deallocation of the instruction queue
InstructionQueue* createQueue(void);
void freeQueue(InstructionQueue* q);

#endif // INSTRUCTION_QUEUE_H

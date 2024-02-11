#ifndef INSTRUCTION_QUEUE_H
#define INSTRUCTION_QUEUE_H

#include <stdio.h>

#define QUEUE_SIZE 16

// Structure to represent the instruction queue
typedef struct {
    int buffer[QUEUE_SIZE]; // Array to store the instructions
    int head;               // Points to the start of the queue
    int tail;               // Points to the end of the queue
    int count;              // Number of items in the queue
} InstructionQueue;

// Function prototypes
void initQueue(InstructionQueue* q);
int isFull(InstructionQueue* q);
int isEmpty(InstructionQueue* q);
int enqueue(InstructionQueue* q, int instruction);
int dequeue(InstructionQueue* q, int* instruction);

#endif // INSTRUCTION_QUEUE_H
#include "InstructionQueue.h"

// Initialize the queue
void initQueue(InstructionQueue* q) {
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

// Check if the queue is full
int isFull(InstructionQueue* q) {
    return q->count == QUEUE_SIZE;
}

// Check if the queue is empty
int isEmpty(InstructionQueue* q) {
    return q->count == 0;
}

// Enqueue an instruction
int enqueue(InstructionQueue* q, int instruction) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return 0;
    }

    q->buffer[q->tail] = instruction;
    q->tail = (q->tail + 1) % QUEUE_SIZE;
    q->count++;
    return 1;
}

// Dequeue an instruction
int dequeue(InstructionQueue* q, int* instruction) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return 0;
    }

    *instruction = q->buffer[q->head];
    q->head = (q->head + 1) % QUEUE_SIZE;
    q->count--;
    return 1;
}
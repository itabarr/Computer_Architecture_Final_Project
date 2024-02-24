#include "InstructionQueue.h"

void initQueue(InstructionQueue* q) {
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

int isFull(InstructionQueue* q) {
    return q->count == QUEUE_SIZE;
}

int isEmpty(InstructionQueue* q) {
    return q->count == 0;
}

int enqueue(InstructionQueue* q, Instruction* instruction) {
    if (isFull(q)) {
        return 0; // Queue is full
    }
    q->buffer[q->tail] = instruction;
    q->tail = (q->tail + 1) % QUEUE_SIZE;
    q->count++;
    return 1; // Success
}

int dequeue(InstructionQueue* q, Instruction** instruction) {
    if (isEmpty(q)) {
        return 0; // Queue is empty
    }
    *instruction = q->buffer[q->head];
    q->head = (q->head + 1) % QUEUE_SIZE;
    q->count--;
    return 1; // Success
}

int preDeque(InstructionQueue* q, Instruction** instruction) {
    if (isEmpty(q)) {
        return 0; // Queue is empty
    }
    *instruction = q->buffer[q->head];
    return 1; // Success
}




InstructionQueue* createQueue() {
    InstructionQueue* q = (InstructionQueue*)malloc(sizeof(InstructionQueue));
    if (q == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    initQueue(q); // Initialize the queue
    return q;
}

void freeQueue(InstructionQueue* q) {
    if (q == NULL) {
        return; // Guard against null pointer
    }

    // Optional: Free any remaining instructions in the queue
    Instruction* instr;
    while (!isEmpty(q)) {
        if (dequeue(q, &instr)) {
            freeInstruction(instr); // Assume this function correctly frees an Instruction object
        }
    }

    // Free the queue structure itself
    free(q);
}

#ifndef CDB_H
#define CDB_H

#include "globals.h"
#include "Instruction.h"

typedef struct {
    ReservationStationTag Tag;
    float Val;
    uint32_t IsReady;
    Instruction *Instruction;
} CDB;

void initCDB(CDB* cdb);

#endif
#pragma once
#include "ReservationStation.h"

typedef struct {
    Operation CDBType;
    ReservationStation Tag;
    float Val;
    Instruction Instruction;
    } CDB;
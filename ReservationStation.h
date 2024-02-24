#pragma once
#define NAME_LEN 20;
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "Instruction.h"
#include "ArithmeticUnits.h"

typedef struct {
    Operation ResType;
    int ResIndex;
} ReservationStationTag;


typedef struct {
    //char[NAME_LEN] Name;
    ReservationStationTag Tag;    
    int d;
    int Vj;
    int Vk;
    int VjValid;
    int VkValid;
    ReservationStationTag Qj;
    ReservationStationTag Qk;
    int ResStationIsBusy;
    Unit ArithUnit;
    int ExectuionDone;
    Instruction Instruction;
    int PC;
} ReservationStation;
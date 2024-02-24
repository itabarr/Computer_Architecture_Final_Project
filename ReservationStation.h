#ifndef RESERVATIONSTATION_H
#define RESERVATIONSTATION_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "ArithmeticUnits.h"
#include "Instruction.h"
#include "ReservationStation.h"
#include "RegisterStatus.h"
#include "CDB.h"
typedef struct {
    // RS Tag
    ReservationStationTag Tag;

    // V's values and Validity
    float Vj;
    float Vk;
    uint32_t VjValid;
    uint32_t VkValid;

    // Q's values and Validity
    ReservationStationTag Qj;
    ReservationStationTag Qk;
    uint32_t QjValid;
    uint32_t QkValid;

    // Is RS busy
    uint32_t IsBusy;

    // Which unit is currenly used
    Unit *ArithUnit;

    // Metadata
    uint32_t ExectuionDone;
    uint32_t IsExectuing;
    Instruction *instruction;

} ReservationStation;

typedef struct {
    ReservationStation* AddStations;
    ReservationStation* MulStations;
    ReservationStation* DivStations;

    uint32_t ADD_size;
    uint32_t MUL_size;
    uint32_t DIV_size;

} ReservationStationArray;


ReservationStationArray* createReservationStationArray(void);
void freeReservationStationArray(ReservationStationArray* rsa);
int IssueInstructionToReservationStationArray(ReservationStationArray* rsa, RegistersTable* regstat, Instruction* instruction);
int IssueInstructionToReservationStation(ReservationStation * rs, RegistersTable * regstat, Instruction * instruction) ;
void FindUnitForStation(ReservationStation* rs, UnitArray* ua);
void FindUnitsForAllStations(ReservationStationArray* rsa , UnitArray* ua);
void ExecuteAllReservationStations(ReservationStationArray* rsa, CDB* AddCDB, CDB* MulCDB, CDB* DivCDB);
#endif // REGISTERS_H

#include "ReservationStation.h"
#include "globals.h"
#include "RegisterStatus.h"
#include "CDB.h";

ReservationStationArray* createReservationStationArray(void) {
    // Allocate the array structure
    ReservationStationArray* rsa = (ReservationStationArray*)malloc(sizeof(ReservationStationArray));
    if (rsa == NULL) {
        perror("Failed to allocate ReservationStationArray");
        return NULL;
    }

    // Total size calculation   
    rsa->ADD_size = ADD_NR_RESERVATION;
    rsa->MUL_size = MUL_NR_RESERVATION;
    rsa->DIV_size = DIV_NR_RESERVATION;

    // Allocate the stations
    rsa->AddStations = (ReservationStation*)malloc(ADD_NR_RESERVATION * sizeof(ReservationStation));
    if (rsa->AddStations == NULL) {
        perror("Failed to allocate ReservationStations");
        free(rsa); // Clean up previously allocated memory
        return NULL;
    }
    rsa->MulStations = (ReservationStation*)malloc(MUL_NR_RESERVATION * sizeof(ReservationStation));
    if (rsa->MulStations == NULL) {
        perror("Failed to allocate ReservationStations");
        free(rsa); // Clean up previously allocated memory
        return NULL;
    }
    rsa->DivStations = (ReservationStation*)malloc(DIV_NR_RESERVATION * sizeof(ReservationStation));
    if (rsa->DivStations == NULL) {
        perror("Failed to allocate ReservationStations");
        free(rsa); // Clean up previously allocated memory
        return NULL;
    }

    // Initialize the stations
    for (uint32_t i = 0; i < ADD_NR_RESERVATION; i++) {
        rsa->AddStations[i].IsBusy = 0;
        rsa->AddStations[i].ExectuionDone = 0;
        rsa->AddStations[i].IsExectuing = 0;
        rsa->AddStations[i].Tag.ResIndex = i+1;
        rsa->AddStations[i].Tag.ResType = OP_ADD;
        
        rsa->AddStations[i].VjValid = 0;
        rsa->AddStations[i].VkValid = 0;
        rsa->AddStations[i].QjValid = 0;
        rsa->AddStations[i].QkValid = 0;

        rsa->AddStations[i].ArithUnit = NULL;
        rsa->AddStations[i].instruction = NULL;

    }
    // Initialize the stations
    for (uint32_t i = 0; i < MUL_NR_RESERVATION; i++) {
        rsa->MulStations[i].IsBusy = 0;
        rsa->MulStations[i].ExectuionDone = 0;
        rsa->MulStations[i].IsExectuing = 0;
        rsa->MulStations[i].Tag.ResIndex = i+1;
        rsa->MulStations[i].Tag.ResType = OP_MUL;

        rsa->MulStations[i].VjValid = 0;
        rsa->MulStations[i].VkValid = 0;
        rsa->MulStations[i].QjValid = 0;
        rsa->MulStations[i].QkValid = 0;

        rsa->MulStations[i].ArithUnit = NULL;
        rsa->MulStations[i].instruction = NULL;

        // Initialize other fields as necessary
    }
    // Initialize the stations
    for (uint32_t i = 0; i < DIV_NR_RESERVATION; i++) {
        rsa->DivStations[i].IsBusy = 0;
        rsa->DivStations[i].ExectuionDone = 0;
        rsa->DivStations[i].IsExectuing = 0;
        rsa->DivStations[i].Tag.ResIndex = i+1;
        rsa->DivStations[i].Tag.ResType = OP_DIV;

        rsa->DivStations[i].VjValid = 0;
        rsa->DivStations[i].VkValid = 0;
        rsa->DivStations[i].QjValid = 0;
        rsa->DivStations[i].QkValid = 0;

        rsa->DivStations[i].ArithUnit = NULL;
        rsa->DivStations[i].instruction = NULL;
        // Initialize other fields as necessary
    }

    return rsa;
}
void freeReservationStationArray(ReservationStationArray* rsa) {
    free(rsa->AddStations);
    free(rsa->MulStations);
    free(rsa->DivStations);
    free(rsa);
}
int IssueInstructionToReservationStationArray(ReservationStationArray* rsa, RegistersTable* regstat,Instruction* instruction) {
    uint32_t i = 0;
    
    switch (instruction->opcode) {
    case ADD:
        for (i = 0; i < ADD_NR_RESERVATION; i++) {
            if (!rsa->AddStations[i].IsBusy) {
                IssueInstructionToReservationStation(&(rsa->AddStations[i]), regstat, instruction);
                return 1;
            }
        }
       
        break;
    case SUB:
        for (i = 0; i < ADD_NR_RESERVATION; i++) {
            if (!rsa->AddStations[i].IsBusy) {
                IssueInstructionToReservationStation(&(rsa->AddStations[i]), regstat, instruction);
                return 1;
            }
        }
        break;
    case MULT:
        for (i = 0; i < MUL_NR_RESERVATION; i++) {
            if (!rsa->MulStations[i].IsBusy) {
                IssueInstructionToReservationStation(&(rsa->MulStations[i]), regstat, instruction);
                return 1;
            }
        }
        // code block
        break;
    case DIV:
        for (i = 0; i < DIV_NR_RESERVATION; i++) {
            if (!rsa->DivStations[i].IsBusy) {
                IssueInstructionToReservationStation(&(rsa->DivStations[i]), regstat, instruction);
                return 1;
            }
        }
        break;
    case HALT:
        break;
    
    default:
        break;
    }
    return 0;
}
int IssueInstructionToReservationStation(ReservationStation *rs , RegistersTable* regstat, Instruction* instruction) {

    FPRegister tmp_src_0 = instruction->src0;
    FPRegister tmp_src_1 = instruction->src1;
    FPRegister tmp_dst   = instruction->dst;
    
    rs->IsBusy = 1;
    rs->instruction = instruction;
    // Handle src0
    if (regstat->QiValid[tmp_src_0] == 0) {
        rs->Vk = regstat->Vi[tmp_src_0];
        rs->VkValid = 1;
        rs->QkValid = 0;

    }
    else {
        rs->Qk = regstat->Qi[tmp_src_0];
        rs->QkValid = 1;
        rs->VkValid = 0;

    }

    // Handle src1
    if (regstat->QiValid[tmp_src_1] == 0) {
        rs->Vj = regstat->Vi[tmp_src_1];
        rs->VjValid = 1;
        rs->QjValid = 0;

    }
    else {
        rs->Qj = regstat->Qi[tmp_src_1];
        rs->QjValid = 1;
        rs->VjValid = 0;

    }
    //Handle Dst
    regstat->Qi[tmp_dst] = rs->Tag;
    regstat->QiValid[tmp_dst] = 1;
    
    return 1;
}

void FindUnitForStation(ReservationStation* rs , UnitArray* ua) {
    Operation cur_op = rs->Tag.ResType;
    uint32_t i;
    switch (cur_op) {
    case OP_ADD:

        for (i = 0; i < ADD_NR_UNITS; i++) {
            if (!ua->AddUnits[i].IsBusy) {
                ua->AddUnits[i].IsBusy = 1;
                ua->AddUnits[i].InternalTimer = ADD_DELAY;
                
                rs->ArithUnit = &(ua->AddUnits[i]);
                rs->IsExectuing = 1;
            }
        }
        break;
    case OP_MUL:
        for (i = 0; i < MUL_NR_UNITS; i++) {
            if (!ua->MulUnits[i].IsBusy) {
                ua->MulUnits[i].IsBusy = 1;
                ua->MulUnits[i].InternalTimer = MUL_DELAY;

                rs->ArithUnit = &(ua->MulUnits[i]);
                rs->IsExectuing = 1;
            }
        }
        break;
    case OP_DIV:
        for (i = 0; i < DIV_NR_UNITS; i++) {
            if (!ua->DivUnits[i].IsBusy) {
                ua->DivUnits[i].IsBusy = 1;
                ua->DivUnits[i].InternalTimer = DIV_DELAY;

                rs->ArithUnit = &(ua->DivUnits[i]);
                rs->IsExectuing = 1;
            }
        }
        break;
    default:
        break;
    }
    return 0;
}

void FindUnitsForAllStations(ReservationStationArray* rsa, UnitArray* ua) {
    uint32_t i;
    ReservationStation *cur_rs;
    for (i = 0; i < ADD_NR_RESERVATION; i++) {
        cur_rs = &(rsa->AddStations[i]);

        if (!cur_rs->IsExectuing & cur_rs->VjValid & cur_rs->VkValid) {
            FindUnitForStation(cur_rs , ua);
        }

    }
    for (i = 0; i < MUL_NR_RESERVATION; i++) {
        cur_rs = &(rsa->MulStations[i]);

        if (!cur_rs->IsExectuing & cur_rs->VjValid & cur_rs->VkValid) {
            FindUnitForStation(cur_rs, ua);
        }

    }
    for (i = 0; i < DIV_NR_RESERVATION; i++) {
        cur_rs = &(rsa->DivStations[i]);

        if (!cur_rs->IsExectuing & cur_rs->VjValid & cur_rs->VkValid) {
            FindUnitForStation(cur_rs, ua);
        }

    }
}

void ExecuteAllReservationStations(ReservationStationArray* rsa , CDB *AddCDB , CDB *MulCDB, CDB *DivCDB) {
    uint32_t i;
    ReservationStation* cur_rs;

    for (i = 0; i < ADD_NR_RESERVATION; i++) {
        cur_rs = &(rsa->AddStations[i]);

        if (cur_rs->IsExectuing) {
            if (cur_rs->ArithUnit->InternalTimer != 0) {
                cur_rs->ArithUnit->InternalTimer--;
            }
            else {
                if (AddCDB->IsReady) {
                    AddCDB->IsReady = 0;

                    if (cur_rs->instruction->opcode == ADD) {
                        AddCDB->Val = cur_rs->Vj + cur_rs->Vk;
                    }

                    if (cur_rs->instruction->opcode == SUB) {
                        AddCDB->Val = cur_rs->Vk - cur_rs->Vj;
                    }

                    
                    AddCDB->Instruction = cur_rs->instruction;
                    AddCDB->Tag = cur_rs->Tag;
                }
            }
        }
    }

    for (i = 0; i < MUL_NR_RESERVATION; i++) {
        cur_rs = &(rsa->MulStations[i]);

        if (cur_rs->IsExectuing) {
            if (cur_rs->ArithUnit->InternalTimer != 0) {
                cur_rs->ArithUnit->InternalTimer--;
            }
            else {
                if (MulCDB->IsReady) {
                    MulCDB->IsReady = 0;
                    MulCDB->Val = cur_rs->Vj * cur_rs->Vk; 
                    MulCDB->Instruction = cur_rs->instruction;
                    MulCDB->Tag = cur_rs->Tag;
                }
            }
        }
    }

    for (i = 0; i < DIV_NR_RESERVATION; i++) {
        cur_rs = &(rsa->DivStations[i]);

        if (cur_rs->IsExectuing) {
            if (cur_rs->ArithUnit->InternalTimer != 0) {
                cur_rs->ArithUnit->InternalTimer--;
            }
            else {
                if (DivCDB->IsReady) {
                    DivCDB->IsReady = 0;
                    DivCDB->Val = (cur_rs->Vj != 0) ? cur_rs->Vk / cur_rs->Vj : 0;
                    DivCDB->Instruction = cur_rs->instruction;
                    DivCDB->Tag = cur_rs->Tag;
                }
            }
        }
    }

}
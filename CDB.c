#include "CDB.h"

void initCDB(CDB* cdb) {
    cdb->Tag.ResIndex = 0;
    cdb->Tag.ResType = 0;
    cdb->Val = 0;
    cdb->IsReady = 1;
    cdb->Instruction = NULL;
}
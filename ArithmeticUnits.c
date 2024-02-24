#include "ArithmeticUnits.h"

UnitArray* createUnitArray(void) {
    UnitArray* ua = (UnitArray*)malloc(sizeof(UnitArray));
    if (!ua) {
        // Allocation failed
        return NULL;
    }
    ua->ADD_size = ADD_NR_UNITS; 
    ua->MUL_size = MUL_NR_UNITS; 
    ua->DIV_size = DIV_NR_UNITS; 

    ua->AddUnits = (Unit*)malloc(ADD_NR_UNITS * sizeof(Unit));
    if (ua->AddUnits == NULL) {
        perror("Failed to allocate ReservationStations");
        free(ua); // Clean up previously allocated memory
        return NULL;
    }

    for (uint32_t i = 0; i < ADD_NR_UNITS; i++) {
        ua->AddUnits[i].InternalTimer = 0;
        ua->AddUnits[i].IsBusy = 0;
    }

    ua->MulUnits = (Unit*)malloc(MUL_NR_UNITS * sizeof(Unit));
    if (ua->MulUnits == NULL) {
        perror("Failed to allocate ReservationStations");
        free(ua); // Clean up previously allocated memory
        return NULL;
    }

    for (uint32_t i = 0; i < MUL_NR_UNITS; i++) {
        ua->MulUnits[i].InternalTimer = 0;
        ua->MulUnits[i].IsBusy = 0;
    }

    ua->DivUnits = (Unit*)malloc(DIV_NR_UNITS * sizeof(Unit));
    if (ua->DivUnits == NULL) {
        perror("Failed to allocate ReservationStations");
        free(ua); // Clean up previously allocated memory
        return NULL;
    }

    for (uint32_t i = 0; i < DIV_NR_UNITS; i++) {
        ua->DivUnits[i].InternalTimer = 0;
        ua->DivUnits[i].IsBusy = 0;
    }
    return ua;
}

void freeUnitArray(UnitArray* ua) {
    free(ua->AddUnits);
    free(ua->MulUnits);
    free(ua->DivUnits);
    free(ua);
}


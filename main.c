#include "stdio.h"
#include "globals.h"
#include "ArithmeticUnits.h"
#include "InstructionQueue.h"
#include "ReservationStation.h"
#include "RegisterStatus.h"
#include "ArithmeticUnits.h"
#include "CDB.h"

void BroadCastCDB(ReservationStationArray* rsa, UnitArray* ua, RegistersTable* reg_stat, CDB* AddCDB, CDB* MulCDB, CDB* DivCDB);

int main() {

	// Load config to global variables
	const char* cfg_file= "C:/Code/Computer_Architecture_Final_Project/inputs/cfg.txt";
	const char* memin_file = "C:/Code/Computer_Architecture_Final_Project/inputs/memin.txt";

	read_config_from_file(cfg_file);
	
	//Load 2 instruction each loop
	Instruction* inst_0 , *inst_1 ,*tmp_instr_0 , *tmp_instr_1;
	InstructionQueue* inst_queue = createQueue();
	ReservationStationArray* rsa = createReservationStationArray();
	UnitArray* ua = createUnitArray();
	
	CDB AddCDB, MulCDB, DivCDB;
	initCDB(&AddCDB); initCDB(&MulCDB); initCDB(&DivCDB);

	RegistersTable d_reg_stat;
	RegistersTable* reg_stat = &d_reg_stat;
	initRegistersTable(reg_stat);

	FILE* memin = fopen(memin_file, "r");

	while (1) {
		int issue_0_succeed = 0;
		int issue_1_succeed = 0;

		// Issue first and second instruction in fifo queue
		if (!isEmpty(inst_queue)) {
			preDeque(inst_queue, &tmp_instr_0);
			issue_0_succeed = IssueInstructionToReservationStationArray(rsa , reg_stat, tmp_instr_0);
			if (issue_0_succeed) dequeue(inst_queue, &tmp_instr_0);
		}
		if ((!isEmpty(inst_queue)) & issue_0_succeed) {
			preDeque(inst_queue, &tmp_instr_1);
			issue_1_succeed = IssueInstructionToReservationStationArray(rsa, reg_stat, tmp_instr_1);
			if (issue_1_succeed) dequeue(inst_queue, &tmp_instr_1);
		}

		// Do matching (find for each reservation station an availble unit if vj and vk are valid)
		FindUnitsForAllStations(rsa, ua);

		// Execute arithmetics (if there is a matched unit - do the calulation after the unit delay)
		ExecuteAllReservationStations(rsa, &AddCDB, &MulCDB, &DivCDB);

		// Brodcast CDB 
		BroadCastCDB(rsa, ua, reg_stat, &AddCDB, &MulCDB, &DivCDB);


		// Fetch from istruction memory to instruction queue
		if (!isFull(inst_queue)){
			inst_0 = get_next_instruction(memin);
			if (inst_0 != NULL) {
				enqueue(inst_queue, inst_0);
			}
			if (!isFull(inst_queue)) {
				inst_1 = get_next_instruction(memin);
				if (inst_1 != NULL){
					enqueue(inst_queue, inst_1);
				}
			}
		}
	}

	freeQueue(inst_queue);
	freeReservationStationArray(rsa);
	freeUnitArray(ua);

	return 0;
	
}

void BroadCastCDB(ReservationStationArray* rsa, UnitArray* ua, RegistersTable* reg_stat, CDB* AddCDB, CDB* MulCDB, CDB* DivCDB) {

	CDB* CDBArray[3] = { AddCDB , MulCDB, DivCDB };
	ReservationStation* StationsArray[3] = { rsa->AddStations  , rsa->MulStations , rsa->DivStations };
	uint32_t NR_RESERVATIONS[3] = { ADD_NR_RESERVATION  , MUL_NR_RESERVATION ,DIV_NR_RESERVATION };


	ReservationStation* curStationsArr;
	ReservationStation curStation;
	CDB* curCDB;

	// Update Qj and Qk tags and validity in reservation stations

	// Outerloop on all CBD
	for (int j = 0; j < 3; j++) {
		curCDB = CDBArray[j];

		// Inner loops on all stations types
		for (int k = 0; k < 3; k++) {
			curStationsArr = StationsArray[k];

			// Inner x2 loop on all the availble stations per type "NR_RESERVATIONS[k]"
			for (int i = 0; i < NR_RESERVATIONS[k]; i++) {
				curStation = curStationsArr[i];

				// Update "j" and "k" values
				if (IsReservationTagEqual(curStation.Qk, curCDB->Tag) & curStation.QkValid & !curCDB->IsReady) {
					curStation.QkValid = 0;
					curStation.Vk = curCDB->Val;
					curStation.VkValid = 1;
				}
				if (IsReservationTagEqual(curStation.Qj, curCDB->Tag) & curStation.QjValid & !curCDB->IsReady) {
					curStation.QjValid = 0;
					curStation.Vj = curCDB->Val;
					curStation.VjValid = 1;
				}
			}
		}
	}
	// Update resitser status table

	// Outer loop on all registers
	for (int i = 0; i < NUM_REGISTERS; i++) {

		// Inner loop on all CDBs
		for (int j = 0; j < 3; j++) {
			curCDB = CDBArray[j];

			// Update register table
			if (IsReservationTagEqual(reg_stat->Qi[i], curCDB->Tag) & reg_stat->QiValid[i] & !curCDB->IsReady) {
				reg_stat->QiValid[i] == 0;
				reg_stat->Vi[i] = curCDB->Val;
			}
		}
	}

	// Clean station and brodcast CDB

	// Outerloop on all CBD
	for (int j = 0; j < 3; j++) {
		curCDB = CDBArray[j];

		// Inner loops on all stations types
		for (int k = 0; k < 3; k++) {
			curStationsArr = StationsArray[k];

			// Inner x2 loop on all the availble stations per type "NR_RESERVATIONS[k]"
			for (int i = 0; i < NR_RESERVATIONS[k]; i++) {
				curStation = curStationsArr[i];

				// Update "j" and "k" values
				if (IsReservationTagEqual(curStation.Tag, curCDB->Tag)) {

					curStation.IsBusy = 0;
					curStation.IsExectuing = 0;
					curStation.VjValid = 0;
					curStation.VkValid = 0;
					curStation.ArithUnit->IsBusy = 0;

					curCDB->IsReady = 1;
					
				}
			}
		}
	}
}


	


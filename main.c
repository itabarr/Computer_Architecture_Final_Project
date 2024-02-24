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
	int i;
	CDB* CDBArray[3] = { AddCDB , MulCDB, DivCDB };

	// Update Qj and Qk tags and validity in reservation stations
	for (int j = 0; j < 3; j++) {
		for (i = 0; i < ADD_NR_RESERVATION; i++) {
			if ((rsa->AddStations[i].Qk.ResIndex == CDBArray[j]->Tag.ResIndex) &&
				(rsa->AddStations[i].Qk.ResType == CDBArray[j]->Tag.ResType) &&
				(rsa->AddStations[i].QkValid == 1) &&
				(CDBArray[j]->IsReady == 0)) {
				rsa->AddStations[i].QkValid = 0;
				rsa->AddStations[i].Vk = CDBArray[j]->Val;
				rsa->AddStations[i].VkValid = 1;
			}
			if ((rsa->AddStations[i].Qj.ResIndex == CDBArray[j]->Tag.ResIndex) &&
				(rsa->AddStations[i].Qj.ResType == CDBArray[j]->Tag.ResType) &&
				(rsa->AddStations[i].QjValid == 1) &&
				(CDBArray[j]->IsReady == 0)) {
				rsa->AddStations[i].QjValid = 0;
				rsa->AddStations[i].Vj = CDBArray[j]->Val;
				rsa->AddStations[i].VjValid = 1;
			}
		}

		for (i = 0; i < MUL_NR_RESERVATION; i++) {
			if ((rsa->MulStations[i].Qk.ResIndex == CDBArray[j]->Tag.ResIndex) &&
				(rsa->MulStations[i].Qk.ResType == CDBArray[j]->Tag.ResType) &&
				(rsa->MulStations[i].QkValid == 1) &&
				(CDBArray[j]->IsReady == 0)) {
				rsa->MulStations[i].QkValid = 0;
				rsa->MulStations[i].Vk = CDBArray[j]->Val;
				rsa->MulStations[i].VkValid = 1;
			}
			if ((rsa->MulStations[i].Qj.ResIndex == CDBArray[j]->Tag.ResIndex) &&
				(rsa->MulStations[i].Qj.ResType == CDBArray[j]->Tag.ResType) &&
				(rsa->MulStations[i].QjValid == 1) &&
				(CDBArray[j]->IsReady == 0)) {
				rsa->MulStations[i].QjValid = 0;
				rsa->MulStations[i].Vj = CDBArray[j]->Val;
				rsa->MulStations[i].VjValid = 1;
			}
		}

		for (i = 0; i < DIV_NR_RESERVATION; i++) {
			if ((rsa->DivStations[i].Qk.ResIndex == CDBArray[j]->Tag.ResIndex) &&
				(rsa->DivStations[i].Qk.ResType == CDBArray[j]->Tag.ResType) &&
				(rsa->DivStations[i].QkValid == 1) &&
				(CDBArray[j]->IsReady == 0)) {
				rsa->DivStations[i].QkValid = 0;
				rsa->DivStations[i].Vk = CDBArray[j]->Val;
				rsa->DivStations[i].VkValid = 1;
			}
			if ((rsa->DivStations[i].Qj.ResIndex == CDBArray[j]->Tag.ResIndex) &&
				(rsa->DivStations[i].Qj.ResType == CDBArray[j]->Tag.ResType) &&
				(rsa->DivStations[i].QjValid == 1) &&
				(CDBArray[j]->IsReady == 0)) {
				rsa->DivStations[i].QjValid = 0;
				rsa->DivStations[i].Vj = CDBArray[j]->Val;
				rsa->DivStations[i].VjValid = 1;
			}
		}
	}


	// Update resitser status table
	for (i = 0; i < NUM_REGISTERS; i++) {
		for (int j = 0; j < 3; j++) {
			if (reg_stat->Qi[i].ResIndex == CDBArray[j]->Tag.ResIndex & reg_stat->Qi[i].ResType == CDBArray[j]->Tag.ResType & reg_stat->QiValid[i] == 1 & CDBArray[j]->IsReady == 0) {
				reg_stat->QiValid[i] == 0;
				reg_stat->Vi[i] = CDBArray[j]->Val;
			}
		}
	}

	for (int j = 0; j < 3; j++) {
		if (CDBArray[j]->IsReady == 0) {
			for (i = 0; i < ADD_NR_RESERVATION; i++) {
				if (CDBArray[j]->Tag.ResIndex == rsa->AddStations->Tag.ResIndex &&
					CDBArray[j]->Tag.ResType == rsa->AddStations->Tag.ResType) {
					rsa->AddStations[i].IsBusy = 0;
					rsa->AddStations[i].IsExectuing = 0;
					rsa->AddStations[i].VjValid = 0;
					rsa->AddStations[i].VkValid = 0;
					CDBArray[j]->IsReady = 1;
					rsa->AddStations[i].ArithUnit->IsBusy = 0;
				}
			}
			for (i = 0; i < MUL_NR_RESERVATION; i++) {
				if (CDBArray[j]->Tag.ResIndex == rsa->MulStations->Tag.ResIndex &&
					CDBArray[j]->Tag.ResType == rsa->MulStations->Tag.ResType) {
					rsa->MulStations[i].IsBusy = 0;
					rsa->MulStations[i].IsExectuing = 0;
					rsa->MulStations[i].VjValid = 0;
					rsa->MulStations[i].VkValid = 0;
					CDBArray[j]->IsReady = 1;
					rsa->MulStations[i].ArithUnit->IsBusy = 0;
				}
			}
			for (i = 0; i < DIV_NR_RESERVATION; i++) {
				if (CDBArray[j]->Tag.ResIndex == rsa->DivStations->Tag.ResIndex &&
					CDBArray[j]->Tag.ResType == rsa->DivStations->Tag.ResType) {
					rsa->DivStations[i].IsBusy = 0;
					rsa->DivStations[i].IsExectuing = 0;
					rsa->DivStations[i].VjValid = 0;
					rsa->DivStations[i].VkValid = 0;
					CDBArray[j]->IsReady = 1;
					rsa->DivStations[i].ArithUnit->IsBusy = 0;
				}
			}
		}
	}

}

	


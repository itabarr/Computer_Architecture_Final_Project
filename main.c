#include "stdio.h"
#include "globals.h"
#include "ArithmeticUnits.h"
#include "InstructionQueue.h"
#include "ReservationStation.h"
#include "RegisterStatus.h"

int main() {

	// Load config to global variables
	const char* cfg_file= "C:/Code/Computer_Architecture_Final_Project/inputs/cfg.txt";
	const char* memin_file = "C:/Code/Computer_Architecture_Final_Project/inputs/memin.txt";

	read_config_from_file(cfg_file);
	
	//Load 2 instruction each loop
	Instruction* inst_0 , *inst_1 ,*tmp_instr_0 , *tmp_instr_1;
	InstructionQueue* inst_queue = createQueue();
	ReservationStationArray* rsa = createReservationStationArray();
	
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

		if (!isEmpty(inst_queue) & issue_0_succeed) {
			preDeque(inst_queue, &tmp_instr_1);
			issue_1_succeed = IssueInstructionToReservationStationArray(rsa, reg_stat, tmp_instr_1);
			if (issue_1_succeed) dequeue(inst_queue, &tmp_instr_1);
		}

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

	return 0;

	
}
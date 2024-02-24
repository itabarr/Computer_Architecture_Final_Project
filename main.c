#include "stdio.h"
#include "config.h"
#include "MemoryAllocation.h"
#include "ArithmeticUnits.h"
#include "InstructionQueue.h"

int main() {

	// Load config to global variables
	const char* cfg_file= "C:/Code/Computer_Architecture_Final_Project/inputs/cfg.txt";
	const char* memin_file = "C:/Code/Computer_Architecture_Final_Project/inputs/memin.txt";

	//read_config_from_file(cfg_file);

	//UNIT_ARRAY = allocateUnitArray();
	//freeUnitArray(UNIT_ARRAY);

	
	//Load 2 instruction each loop
	Instruction* inst_0 , *inst_1;
	InstructionQueue* inst_queue = createQueue();

	FILE* memin = fopen(memin_file, "r");

	while (1) {
		if ((inst_0 = get_next_instruction(memin)) == NULL) {
			break;
		}

		enqueue(inst_queue, inst_0);
		// decide wether to push the instruction queue
		// decide if to take the second one
		if ((inst_1 = get_next_instruction(memin)) == NULL) {
			break;
		}
		enqueue(inst_queue, inst_1);

	}

	freeQueue(inst_queue);

	return 0;

	
}
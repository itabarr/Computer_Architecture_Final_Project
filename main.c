#include "stdio.h"
#include "config.h"
#include "MemoryAllocation.h"
#include "ArithmeticUnits.h"

int main() {

	// Load config to global variables
	const char* cfg_file= "C:/Code/Computer_Architecture_Final_Project/inputs/cfg.txt";
	const char* memin_file = "C:/Code/Computer_Architecture_Final_Project/inputs/memin.txt";

	//read_config_from_file(cfg_file);

	//UNIT_ARRAY = allocateUnitArray();
	//freeUnitArray(UNIT_ARRAY);

	printInstructionsFromFile(memin_file);
	return 0;

	
}
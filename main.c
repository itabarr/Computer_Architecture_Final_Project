#include "stdio.h"
#include "config.h"
#include "MemoryAllocation.h"
#include "ArithmeticUnits.h"

int main() {


	// Load config to global variables
	char cfg_file[256] = "C:/Code/Computer_Architecture_Final_Project/inputs/cfg.txt";
	read_config_from_file(cfg_file);

	UNIT_ARRAY = allocateUnitArray();


	freeUnitArray(UNIT_ARRAY);
}
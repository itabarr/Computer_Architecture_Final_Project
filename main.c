#include "stdio.h"
#include "config.h"

int main() {


	// Load config to global variables
	char cfg_file[256] = "C:/Code/Computer_Architecture_Final_Project/inputs/cfg.txt";
	read_config_from_file(cfg_file);
	printf("ADD_DELAY %d\n" , ADD_DELAY);
	printf("DIV_DELAY %d", DIV_DELAY);
	
}
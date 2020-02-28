#include "data_structure.h"
const char * opcodeTable[16] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};
/**addressMethod addressTable[16];
addressTable[0]->src = 15;
addressTable[0]->dst = 7;
addressTable[1].src = 15; 
addressTable[1].dst = 15; 
addressTable[2].src = 15;
addressTable[2].dst = 7;
addressTable[3].src = 15;
addressTable[3].dst = 7;
addressTable[4].src = 4;
addressTable[4].dst = 7; 
addressTable[5].src = 0;
addressTable[5].dst = 7; 
addressTable[6].src = 0;
addressTable[6].dst = 7; 
addressTable[7].src = 0;
addressTable[7].dst = 7; 
addressTable[8].src = 0;
addressTable[8].dst = 7; 
addressTable[9].src = 0;
addressTable[9].dst = 6; 
addressTable[10].src = 0;
addressTable[10].dst = 6;    
addressTable[11].src = 0;
addressTable[11].dst = 7;  
addressTable[12].src = 0;
addressTable[12].dst = 15; 
addressTable[13].src = 0;
addressTable[13].dst = 6;  
addressTable[14].src = 0;
addressTable[14].dst = 0;
addressTable[15].src = 0;
addressTable[15].dst = 0; **/

int find_opcode(char * opcode)
{
	int i;
	
	for(i = 0; i<16; i++)
	{
		if (strcmp(opcode, opcodeTable[i]) == 0)
			return i;
	}
	return -1;
}


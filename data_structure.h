#define MAX_LINE 0;
#define MAX_FILE 0;
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/**typedef struct PSW{
	uint16_t ERROR : 1;
	uint16_t LABEL : 1;
	uint16_t Z : 1;
}PSW_hold;**/
/**first code word**/
typedef struct codeWord{
	 uint16_t ARE : 3;
	 uint16_t dst : 4;
	 uint16_t src : 4;
	 uint16_t opcode : 4;
}codeWord;

/**second/third code wird, a data word with direct/immidiate address method**/
typedef struct infoWordData{
	 uint16_t ARE : 3;
	 uint16_t data : 12;
}infoWordData;	

/**second/third code wird, a data word with direct register/indirect register address method**/
typedef struct infoWordReg{
	 uint16_t ARE : 3;
	 uint16_t srcReg : 3;
	 uint16_t dstReg : 3;
	 uint16_t rest : 6;
}infoWordReg;

typedef union u_ptr{
	codeWord * codeWordPtr;
	infoWordData * dataWordPtr;
	infoWordReg * regWordPtr;
}wordPtr;
/**data word (data/string)**/
typedef struct dataWord{
	 uint16_t data : 15;
}dataWord;

typedef struct memWord* memWordPtr;

/**a structure to hold a memory word, from one of the optional types/
typedef union wordType{
	codeWord c_word;
	infoWordData info_d_word;
	infoWordReg info_r_word;
	dataWord d_word;

}wordType;**/

/**memory word, with the value and address (and the next word for the inked list)**/
typedef struct memWord{
	uint16_t word;
	uint16_t index;
	memWordPtr next;
}memWord;
/**
typedef struct error* errorPtr;

typedef struct error{
	uint16_t lineNum;
	int errorType;
	errorPtr next;
}error;
**/

typedef struct addressMethod *addrMethodPtr;

typedef struct addressMethod{
	uint8_t src : 4;
	uint8_t dst : 4;
}addressMethod;

/**
addressMethod addressTable[16];
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
addressTable[15].dst = 0; 
**/
typedef struct label * labelPtr;
typedef struct label
{
	char * labelName;
	uint32_t value;
	uint8_t LabelType;
	labelPtr next;
}label;


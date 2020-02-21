#define MAX_LINE 0;
#define MAX_FILE 0;

/*flags*/
typedef struct PSW{
	uint16_t ERROR : 1;
	uint16_t LABEL : 1;
	uint16_t Z : 1;
}

typedef struct codeWord{
	 uint16_t ARE : 3;
	 uint16_t d : 4;
	 uint16_t s : 4;
	 uint16_t opcode : 4;
}codeWord;

typedef struct infoWordData{
	 uint16_t ARE : 3;
	 uint16_t data : 12;
}infoWordData;	

typedef struct infoWordReg{
	 uint16_t ARE : 3;
	 uint16_t srcReg : 3;
	 uint16_t dstReg : 3;
	 uint16_t rest : 6;
}infoWordReg;

typedef struct dataWord{
	 uint16_t data : 15;
}dataWord;

//word in memory
uint16_t word;

typedef struct memWord* memWordPtr;

typedef struct memWord{
	uint16_t word;
	uint16_t index;
	memWordPtr next;
}memWord;

typedef struct error* errorPtr;

typedef struct error{
	uint16_t lineNum;
	char * errorType;
	errorPtr next;
}errorPtr;

const char * opcodeTable{"mov", "cmp", "add", "sub",
		         "lea", "clr", "not", "inc", 
 		         "dec", "jmp", "bne", "red", 
		         "prn", "jsr", "rts", "stop"};

typedef struct addressMethod{
	uint8_t src : 4;
	uint8_t dst : 4;
}addressMethod;

addressMethod addressTable[16];
addressTable[0] = {15, 7};
addressTable[1] = {15, 15}; 
addressTable[2] = {15, 7}; 
addressTable[3] = {15, 7}; 
addressTable[4] = {4, 7}; 
addressTable[5] = {0, 7}; 
addressTable[6] = {0, 7}; 
addressTable[7] = {0, 7}; 
addressTable[8] = {0, 7}; 
addressTable[9] = {0, 6}; 
addressTable[10] = {0, 6}; 
addressTable[11] = {0, 7}; 
addressTable[12] = {0, 15}; 
addressTable[13] = {0, 6}; 
addressTable[14] = {0, 0}; 
addressTable[15] = {0, 0};

/*const char * registers ["r0,"r1","r2","r3","r4","r5","r6","r7"]*/

typedef struct label * labelPtr;
typedef struct label
{
	char * labelName;
	uint32_t value;
	uint8_t LabelType;
	labelPtr next;
}label;


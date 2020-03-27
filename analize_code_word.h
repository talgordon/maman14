#define MAX_FILE 0;
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define A 4
#define R 2
#define E 1
#define OPCODE_LENGTH 4
#define DST_CODE_LENGTH 4
#define SRC_CODE_LENGTH 4
#define ARE_LENGTH 3
#define INFO_LENGTH 12
#define SRC_DATA_LENGTH 3
#define DST_DATA_LENGTH 3
#define REST_LENGTH 6
#define DATA_LENGTH 15
#define EMPTY 0
#define MAX_MEMORY 4096

typedef struct codeWord{
	 unsigned int ARE : ARE_LENGTH;
	 unsigned int dst : DST_CODE_LENGTH;
	 unsigned int src : SRC_CODE_LENGTH;
	 unsigned int opcode : OPCODE_LENGTH;
}codeWord;

/**second/third code wird, a data word with direct/immidiate address method**/
typedef struct infoWordData{
	 unsigned int ARE : ARE_LENGTH;
	 unsigned int data : INFO_LENGTH;
}infoWordData;	

/**second/third code wird, a data word with direct register/indirect register address method**/
typedef struct infoWordReg{
	 unsigned int ARE : ARE_LENGTH;
	 unsigned int srcReg : SRC_DATA_LENGTH;
	 unsigned int dstReg : DST_DATA_LENGTH;
	 unsigned int rest : REST_LENGTH;
}infoWordReg;

typedef union u_ptr{
	codeWord * codeWordPtr;
	infoWordData * dataWordPtr;
	infoWordReg * regWordPtr;
}wordPtr;

/**data word (data/string)**/
typedef struct dataWord{
	 unsigned int data : DATA_LENGTH;
}dataWord;

/**memory word, with the value and address (and the next word for the inked list)**/
typedef struct memWord* memWordPtr;

typedef struct memWord{
	unsigned int word;
	unsigned int index;
	memWordPtr next;
}memWord;

enum types{CODE_WORD, DATA_WORD, DATA_REG_WORD};

memWordPtr data_head;
unsigned int buffer[MAX_MEMORY];

void write_data_image(dataWord dWord);
void write_code_image(wordPtr ptr, int type);
void print_mem();

/*A function that find the opcode in the array*/
int find_opcode(char * opcode);
/*A function that encodes insruction to binary memory word*/
void translate_code(wordPtr wPtr, int opcode, int srcType, int dstType);
void finish_translate(char *line, wordPtr wPtr);
/*A function that encodes guidance to binary memory word*/
void translate_data(int type, char * line);



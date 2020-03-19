#define MAX_LINE 0;
#define MAX_FILE 0;
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct codeWord{
	 unsigned int ARE : 3;
	 unsigned int dst : 4;
	 unsigned int src : 4;
	 unsigned int opcode : 4;
}codeWord;

/**second/third code wird, a data word with direct/immidiate address method**/
typedef struct infoWordData{
	 unsigned int ARE : 3;
	 unsigned int data : 12;
}infoWordData;	

/**second/third code wird, a data word with direct register/indirect register address method**/
typedef struct infoWordReg{
	 unsigned int ARE : 3;
	 unsigned int srcReg : 3;
	 unsigned int dstReg : 3;
	 unsigned int rest : 6;
}infoWordReg;

typedef union u_ptr{
	codeWord * codeWordPtr;
	infoWordData * dataWordPtr;
	infoWordReg * regWordPtr;
}wordPtr;
/**data word (data/string)**/
typedef struct dataWord{
	 unsigned int data : 15;
}dataWord;


/**a structure to hold a memory word, from one of the optional types**/
typedef union wordType{
	codeWord c_word;
	infoWordData info_d_word;
	infoWordReg info_r_word;
	dataWord d_word;

}wordType;

/**memory word, with the value and address (and the next word for the inked list)**/



typedef struct memWord* memWordPtr;

typedef struct memWord{
	unsigned int word;
	unsigned int index;
	memWordPtr next;
}memWord;

enum types{CODE_WORD, DATA_WORD, DATA_REG_WORD};

memWordPtr dataHead;

unsigned int buffer[4096];

int write_data_image(dataWord dWord);
int write_code_image(wordPtr ptr, int type);
int print_mem();
int two_complement(int num);

int find_opcode(char * opcode);
int translate_code(wordPtr wPtr, int opcode, int srcType, int dstType);
int finish_translate(char *line, wordPtr wPtr);
int translate_data(int type, char * line);



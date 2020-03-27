#include <ctype.h>
#define MAX_WORD 80
#define MAX_LINE 127
#define NO_OPERAND 0
#define IMMEDIATE 1
#define DIRECT 2
#define INDIRECT_REGISTER 4
#define DIRECT_REGISTER 8
#define FIRST 1
#define SECOND 2
#define MAX_REGISTER 8
#define MIN_REGISTER 0
#define NUM_OF_ADDRESS_METHOD 4
#define NUM_OF_OPCODE 16
	
unsigned int DC;
unsigned int IC;
unsigned int L;
char * inputLine;

/*Enum with the types possible*/
typedef enum type{LABEL , DATA , STRING , EXTERN , ENTRY, CODE, END} types;

typedef struct addressMethod *addrMethodPtr;

/*A structure that represents valid addressing methods fot each opcode*/
typedef struct addressMethod{
	unsigned int src : NUM_OF_ADDRESS_METHOD;
	unsigned int dst : NUM_OF_ADDRESS_METHOD;
}addressMethod;

/*An array with all the opcode is possible*/
addressMethod addressTable[NUM_OF_OPCODE];

/*A function that skip white spaces.*/
void skip_spaces(char **line);
/*A function that check if the end of the line is legal - doesn't contain any characters which are not a white space*/
void legal_EOL(char ** line);
/*A function that checks for a comma or not and advances the line accordingly*/
void comma_logic(char **line);
/*A function that breaks down an input line and returns the following data every time*/
int get_data(char **line);
/*A function that check if the line is label and return 0/1*/
int is_label(char * line);
/*A function that analize an input line. Reads a first word from the line to the space and returns an enum according to the type it has inserted*/
types get_word(char * line[], char ** word);
/*A function that analize a line from the input, reads the operands in the insruction*/
void get_operand(char * line, int * srcType, int *dstType, char ** srcName, char ** dstName, int loop);


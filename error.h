#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR -1
#define SUCCESS 0
#define IS_TRUE 1
#define IS_FALSE 0
#define NO_ADDRESS 0

typedef struct PSW{
	unsigned int ERR: 1;
	unsigned int LABEL: 1;
	unsigned int Z: 1;
}PSW_hold;

typedef struct error* errorPtr;

/*Struct of error with the line number of line and the type of error*/
typedef struct error{
	unsigned int lineNum;
	unsigned int errorType;
	errorPtr next;
}error;

errorPtr error_head;
/*An enum with all the type of error*/
enum errType{ALLOCATE, UNEXISTED_LABEL,TOO_MANY_OPERANDS, TOO_FEW_OPERANDS, INVALID_SRC_TYPE, INVALID_DST_TYPE, UNEXISTED_OPCODE, INVALID_LABEL_NAME, MISSING_COMMA, MULTIPLE_COMMA, INVALID_DATA, MULTIPLE_LABEL, MISSING_QUOTATION, INVALID_REG, TOO_LONG_LABEL, CANNOT_OPEN_FILE, RESERVED_LABEL_NAME, MISSING_DATA};

PSW_hold PSW;
int line_num;

/*void error_check(char *err);*/

/*A function that add error to a linked list of errors*/
void add_error(int type);
/*A function that print a error in the linked list with error*/
void print_error();
/*A function that returns the value of the flag in the data structure*/
int get_flag(char * name);
/*A function that lights a flag in the data structrue*/
void set_flag(char *name, int value);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR -1
#define SUCCESS 0
#define NO_ADDRESS 0

typedef struct PSW{
	unsigned int ERR : 1;
	unsigned int LABEL : 1;
	unsigned int Z : 1;
}PSW_hold;

typedef struct error* errorPtr;

typedef struct error{
	unsigned int lineNum;
	unsigned int errorType;
	errorPtr next;
}error;

errorPtr error_head;
enum errType{ALLOCATE, UNEXISTED, FLAG_NOT_EXIST,CANNOT_OPEN_FILE, LINE_INVALID, INVALID_DATA, OPCODE, UNDEFINE_WORD};
	
PSW_hold PSW;
extern int line_num;
void error_check(char *err);
void add_error(int type);
void print_error();
int get_flag(char * name);
void set_flag(char *name, int value);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR -1
#define SUCCESS 0
#define NO_ADDRESS 0

typedef struct PSW{
	unsigned int ERR: 1;
	unsigned int LABEL: 1;
	unsigned int Z: 1;
}PSW_hold;

typedef struct error* errorPtr;

typedef struct error{
	unsigned int lineNum;
	unsigned int errorType;
	errorPtr next;
}error;

errorPtr error_head;
enum errType{ALLOCATE, UNEXISTED_LABEL,TOO_MANY_OPERANDS, TOO_FEW_OPERANDS, INVALID_SRC_TYPE, INVALID_DST_TYPE, UNEXISTED_OPCODE, INVALID_LABEL_NAME, MISSING_COMMA, MULTIPLE_COMMA, INVALID_DATA, MULTIPLE_LABEL, MISSING_QUOTATION, INVALID_REG, TOO_LONG_LABEL, CANNOT_OPEN_FILE, RESERVED_LABEL_NAME};

PSW_hold PSW;
int line_num;
void error_check(char *err);
void add_error(int type);
void print_error();
int get_flag(char * name);
void set_flag(char *name, int value);

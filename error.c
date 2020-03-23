#include "error.h"

void add_error(int type)
{
	errorPtr tmp, newError;
	if (error_head == NULL)
	{	
		set_flag("ERROR", 1);
		error_head = (errorPtr)malloc(sizeof(error));
		if(error_head == NULL)
			add_error(ALLOCATE);
		error_head->errorType = type;
		error_head->lineNum = line_num;
		error_head->next = NULL;
	}
	else
	{
		tmp = (errorPtr)malloc(sizeof(error));
		newError = (errorPtr)malloc(sizeof(error));
		if((tmp == NULL)||(newError == NULL))
			add_error(ALLOCATE);
		tmp = error_head;
		while(tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		newError->errorType = type;
		newError->lineNum = line_num;
		newError->next = NULL;
		tmp->next = newError;
	}
}

void print_error()
{
	errorPtr tmp;
	tmp = (errorPtr)malloc(sizeof(error));
	if(tmp == NULL)
		add_error(ALLOCATE);
	tmp = error_head;
	while(tmp != NULL)
	{
		switch(tmp->errorType)
		{
			case ALLOCATE:
				fprintf(stderr, "can not allocate memory");
				break;
			case UNEXISTED_LABEL:
				fprintf(stderr, "there is no label with this name");
				break;
			case TOO_MANY_OPERANDS:
				fprintf(stderr, "there are too many operands after opcode");
				break;
			case TOO_FEW_OPERANDS:
				fprintf(stderr, "there are too few operands after opcode");
				break;
			case INVALID_SRC_TYPE:
				fprintf(stderr, "the address method of the source operand is illegal");
				break;
			case INVALID_DST_TYPE:
				fprintf(stderr, "the address method of the destination operand is illegal");
				break;
			case UNEXISTED_OPCODE:
				fprintf(stderr, "there is no opcode with this name");
				break;
			case INVALID_LABEL_NAME:
				fprintf(stderr, "the name of the label is illegal");
				break;
			case MISSING_COMMA:
				fprintf(stderr, "a comma is missing");
				break;
			case MULTIPLE_COMMA:
				fprintf(stderr, "there are multiple consecutive commas");
				break;
			case INVALID_DATA:
				fprintf(stderr, "the data is illegal");
				break;
			case MULTIPLE_LABEL:
				fprintf(stderr, "there is already a label with this name");
				break;
			case MISSING_QUOTATION:
				fprintf(stderr, "missing quotation marks before or after string");
				break;
			case INVALID_REG:
				fprintf(stderr, "there is no register with this name");
				break;
			case TOO_LONG_LABEL:
				fprintf(stderr, "the label's name is too long - over 31 characters");
				break;
			case CANNOT_OPEN_FILE:
				fprintf(stderr, "failed in openning the file");
				break;
			case RESERVED_LABEL_NAME:
				fprintf(stderr, "the label's name is illegal - is a reserved word");
				break;
		}	
		fprintf(stderr, ", in line:%d\n", tmp->lineNum+1);
		tmp = tmp->next;	
	}
}

int get_flag(char * name)
{
	if (strcmp(name, "ERROR") == 0)
		return PSW.ERR;
	if (strcmp(name, "LABEL") == 0)
		return PSW.LABEL;
	if (strcmp(name, "Z") == 0)
		return PSW.Z;
	return ERROR;
}

void set_flag(char *name, int value)
{
	if (strcmp(name, "ERROR") == 0)
		PSW.ERR = value;
	else
	{
		if (strcmp(name, "LABEL") == 0)
			PSW.LABEL = value;
		else
		{   
			if (strcmp(name, "Z") == 0)
				PSW.Z = value;	
		}
	}
}



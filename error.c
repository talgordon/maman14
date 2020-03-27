#include "error.h"

/*A function that add error to a linked list of errors*/
void add_error(int type)
{
	errorPtr tmp, newError;
	if (error_head == NULL)/*If the linked list is empty*/
	{	
		set_flag("ERROR", IS_TRUE);/*Turns on the error flag*/
		error_head = (errorPtr)malloc(sizeof(error));
		if(error_head == NULL)/*If could not allocate space*/
		{
			add_error(ALLOCATE);/*Print error in allocation place*/
			return;
		}
		error_head->errorType = type;/*Initializes the type in a linked list*/
		error_head->lineNum = line_num;/*Initializes the line num in a linked list*/
		error_head->next = NULL;/*Initializes the pointer to NULL*/
	}
	else/*If have a node in a linked list*/
	{
		tmp = (errorPtr)malloc(sizeof(error));
		newError = (errorPtr)malloc(sizeof(error));
		if((tmp == NULL)||(newError == NULL))/*If could not allocate space*/
		{
			add_error(ALLOCATE);/*Print error in allocation place*/
			return;
		}
		tmp = error_head;/*Initializes tmp to the top of the list*/
		while(tmp->next != NULL)/*Loop that run as long as the tmp equal to NULL-end of the list*/
		{
			tmp = tmp->next;/*Initializes the pointer to next node*/
		}
		newError->errorType = type;/*Initializes the type in a linked list*/
		newError->lineNum = line_num;/*Initializes the line num in a linked list*/
		newError->next = NULL;/*Initializes the pointer to NULL*/
		tmp->next = newError;
	}
}

/*A function that print a error in the linked list with error*/
void print_error()
{
	errorPtr tmp;
	tmp = (errorPtr)malloc(sizeof(error));
	if(tmp == NULL)/*If tmp equal to NULL*/
	{
		add_error(ALLOCATE);/*Print error in allocation place*/
		return;		
	}
	tmp = error_head;
	while(tmp != NULL)/*Loop that run as long as the tmp equal to NULL-end of the list*/
	{
		switch(tmp->errorType)/*Switch depending on the type of error. Finds the appropriate error, prints the error type to the user, and leaves the loop.*/
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
			case MISSING_DATA:
				fprintf(stderr, "missing any data after '.data' or '.string'");
				break;
		}	
		fprintf(stderr, ", in line:%d\n", tmp->lineNum+1);
		tmp = tmp->next;	
	}
	free(tmp);
}

/*A function that returns the value of the flag in the data structure*/
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

/*A function that lights a flag in the data structrue*/
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



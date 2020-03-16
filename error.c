#include "error.h"
/**
int main()
{
	error_check("ALLOCATE");
	error_check("UNEXISTED");
	error_check("ALLOCATE");
	return 0;
}**/
void error_check(char *err)
{
	set_flag("ERROR", 1);
	if (strcmp(err, "ALLOCATE") == 0)
		add_error(ALLOCATE);
	if (strcmp(err, "UNEXISTED") == 0)
		add_error(UNEXISTED);
}

void add_error(int type)
{
	errorPtr tmp, newError;
	if (error_head == NULL)
	{	
		error_head = (errorPtr)malloc(sizeof(error));
		if(error_head == NULL)
			error_check("ALLOCATE");
		error_head->errorType = type;
		error_head->lineNum = line_num;
		error_head->next = NULL;
	}
	else
	{
		tmp = (errorPtr)malloc(sizeof(error));
		newError = (errorPtr)malloc(sizeof(error));
		if((tmp == NULL)||(newError == NULL))
			error_check("ALLOCATE");
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
		error_check("ALLOCATE");
	tmp = error_head;
	while(tmp != NULL)
	{
		switch(tmp->errorType)
		{
			case ALLOCATE:
				fprintf(stderr, "can not allocate memory");
				break;
			case UNEXISTED:
				fprintf(stderr, "the label is not exists");
				break;
			default:
				fprintf(stderr, "error in code");
		}	
		fprintf(stderr, ", in line:%d\n", tmp->lineNum);
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
	error_check("FLAG_NOT_EXIST");
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
			else
				error_check("FLAG_NOT_EXIST");
		}
	}
}



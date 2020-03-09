#include "flag.c"
#define ERROR 1
#define SUCCESS 0

typedef struct error* errorPtr;

typedef struct error{
	uint16_t lineNum;
	int errorType;
	errorPtr next;
}error;

errorPtr head;
enum errType{ALLOCATE, UNEXISTED};

int line_num;
int error_check(char *err);
int add_error(int type);
int print_error();
   
int error_check(char *err)
{
	set_flag("ERROR", 1);
	if (strcmp(err, "ALLOCATE") == 0)
		add_error(ALLOCATE);
	if (strcmp(err, "UNEXISTED") == 0)
		add_error(UNEXISTED);
	return 0;
}

int add_error(int type)
{
	errorPtr tmp, newError;
	if (head == NULL)
	{	
		head = (errorPtr)malloc(sizeof(error));
		if(head == NULL)
			return ERROR;
		head->errorType = type;
		head->lineNum = line_num;
		head->next = NULL;
		return SUCCESS;
	}
	else
	{
		tmp = (errorPtr)malloc(sizeof(error));
		newError = (errorPtr)malloc(sizeof(error));
		if((tmp == NULL)||(newError == NULL))
			return ERROR;
		tmp = head;
		while(tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		newError->errorType = type;
		newError->lineNum = line_num;
		newError->next = NULL;
		tmp->next = newError;
		return SUCCESS;
	}
}

int print_error()
{
	errorPtr tmp;
	tmp = (errorPtr)malloc(sizeof(error));
	if(tmp == NULL)
		return ERROR;
	tmp = head;
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
	return SUCCESS;
}

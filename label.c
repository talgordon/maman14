#include "data_structure.h"

enum status{SUCCESS, ALLOCATE_ERROR, EXISTENCE_ERROR, UNEXISTENCE_ERROR};
enum labeltypes{UNDEFINED, DATA, ENTRY, EXTERN, CODE};
enum labelFields{NAME, VALUE, TYPE};

labelPtr head;

int add_label(char * name, int value, int type);
int get_label(char *name, int feature, int featureType, labelPtr* label);
int update_label(int update, int updateType, char *name);
int print_label();


int print_label()
{
	labelPtr tmp;
	tmp = (labelPtr)malloc(sizeof(label));
	if(tmp == NULL)
		return ALLOCATE_ERROR;
	tmp = head;
	while(tmp != NULL)
	{
		printf("\n%s, %d, ", tmp->labelName, tmp->value);
		if(tmp->LabelType == DATA)
			printf("data\n");
		if(tmp->LabelType == ENTRY)
			printf("entry\n");
		if(tmp->LabelType == EXTERN)
			printf("extern\n");
		if(tmp->LabelType == CODE)
			printf("code\n");
		if(tmp->LabelType == UNDEFINED)
			printf("undefined\n");
		tmp = tmp->next;	
	}
	return SUCCESS;
}

int add_label(char * name, int value, int type)
{
	labelPtr tmp, newLabel;
	if (head == NULL)
	{	
		head = (labelPtr)malloc(sizeof(label));
		head->labelName = (char *)malloc(sizeof(name)*sizeof(char));
		if((head->labelName == NULL)||(head == NULL))
			return ALLOCATE_ERROR;
		strcpy(head->labelName, name);
		head->value = value;
		head->LabelType = type;
		head->next = NULL;
		return SUCCESS;
	}
	else
	{
		tmp = (labelPtr)malloc(sizeof(label));
		newLabel = (labelPtr)malloc(sizeof(label));
		if((tmp == NULL)||(newLabel == NULL))
			return ALLOCATE_ERROR;
		tmp = head;
		while(tmp->next != NULL)
		{
			if(strcmp(tmp->labelName,name) == 0)
				return EXISTENCE_ERROR;/**error**/
			tmp = tmp->next;
		}
		newLabel->labelName = (char *)malloc(sizeof(name)*sizeof(char));
		strcpy(newLabel->labelName, name);
		newLabel->value = value;
		newLabel->LabelType = type;
		newLabel->next = NULL;
		tmp->next = newLabel;
		return SUCCESS;
	}
}

int get_label(char *name, int feature, int featureType, labelPtr* label)
{
	if(*label == NULL)
		return ALLOCATE_ERROR;
	*label = head;
	while(*label != NULL)
	{
		if((featureType == NAME) && (strcmp((*label)->labelName,name) == 0))	
			return SUCCESS;
		if((featureType == VALUE) && (feature == (*label)->value))	
			return SUCCESS;
		if((featureType == TYPE) && (feature == (*label)->LabelType))
			return SUCCESS;
		*label = (*label)->next;
	}
	return UNEXISTENCE_ERROR;
}

int update_label(int update, int updateType, char *name)
{
	labelPtr tmp;
	tmp = (labelPtr)malloc(sizeof(label));
	if(tmp == NULL)
		return ALLOCATE_ERROR;
	tmp = head;
	while(tmp != NULL)
	{
		if(strcmp(tmp->labelName, name) == 0)
		{
			if(updateType == VALUE)
			{
				tmp->value = update;
				return SUCCESS;
			}
			if(updateType == TYPE)
			{
				tmp->LabelType = update;
				return SUCCESS;
			}		
		}
		tmp = tmp->next;
	}
	return UNEXISTENCE_ERROR;
}







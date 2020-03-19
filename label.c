#include "error.h"
#include "label.h"
/**
int main()
{
	labelPtr tmp;
	tmp = (labelPtr)malloc(sizeof(label));

	add_label("MAIN", 130, ENTRY_LABEL);
	add_label("LIST", 143, DATA_LABEL);
	add_label("END", 147, CODE_LABEL);
		
	get_label(NULL, ENTRY_LABEL, LABEL_TYPE, &tmp);
	update_label(EXTERN_LABEL, LABEL_TYPE, tmp->labelName);
	
	print_label();
	return 0;	
}**/
void print_label()
{
	labelPtr tmp;
	tmp = (labelPtr)malloc(sizeof(label));
	if(tmp == NULL)
	{
		error_check("ALLOCATE");
	}
	tmp = label_head;
	while(tmp != NULL)
	{
		printf("\n%s, %d, ", tmp->labelName, tmp->labelValue);
		if(tmp->labelType == DATA_LABEL)
			printf("data\n");
		if(tmp->labelType == ENTRY_LABEL)
			printf("entry\n");
		if(tmp->labelType == EXTERN_LABEL)
			printf("extern\n");
		if(tmp->labelType == CODE_LABEL)
			printf("code\n");
		if(tmp->labelType == UNDEFINED_LABEL)
			printf("undefined\n");
		tmp = tmp->next;	
	}
}

void add_label(char * name, int value, int type)
{
	labelPtr tmp, newLabel;
	if (label_head == NULL)
	{	
		label_head = (labelPtr)malloc(sizeof(label));
		label_head->labelName = (char *)malloc(sizeof(name)*sizeof(char));
		if((label_head->labelName == NULL)||(label_head == NULL))
		{
			error_check("ALLOCATE");
		}
		strcpy(label_head->labelName, name);
		label_head->labelValue = value;
		label_head->labelType = type;
		label_head->next = NULL;
	}
	else
	{
		tmp = (labelPtr)malloc(sizeof(label));
		newLabel = (labelPtr)malloc(sizeof(label));
		if((tmp == NULL)||(newLabel == NULL))
		{
			error_check("ALLOCATE");
		}
		tmp = label_head;
		while(tmp->next != NULL)
		{
			if(strcmp(tmp->labelName,name) == 0)
			{
				error_check("EXISTED");
			}
			tmp = tmp->next;
		}
		newLabel->labelName = (char *)malloc(sizeof(name)*sizeof(char));
		if (newLabel->labelName == NULL)
		{
			error_check("ALLOCATE");
		}
		strcpy(newLabel->labelName, name);
		newLabel->labelValue = value;
		newLabel->labelType = type;
		newLabel->next = NULL;
		tmp->next = newLabel;
	}
}

void get_label(char *name, int feature, int featureType, labelPtr* label)
{
	if(*label == NULL)
	{
		error_check("ALLOCATE");
		return;
	}
	*label = label_head;
	while(*label != NULL)
	{
		if((featureType == LABEL_NAME) && (strcmp((*label)->labelName,name) == 0))	
			return;
		if((featureType == LABEL_VALUE) && (feature == (*label)->labelValue))	
			return;
		if((featureType == LABEL_TYPE) && (feature == (*label)->labelType))
			return;
		*label = (*label)->next;
	}
	*label = NULL;
	error_check("UNEXISTED");
}

int update_label(int update, int updateType, int labelType, char *name)
{
	labelPtr tmp;
	tmp = (labelPtr)malloc(sizeof(label));
	if(tmp == NULL)
	{
		error_check("ALLOCATE");
		return ERROR;
	}	
	tmp = label_head;
	while(tmp != NULL)
	{
		if((strcmp(tmp->labelName, name) == 0)||(strcmp(name, "ALL") == 0)&&(tmp->labelType == labelType))
		{
			if(updateType == LABEL_VALUE)
			{
				tmp->labelValue+= update;
				return SUCCESS;
			}
			if(updateType == LABEL_TYPE)
			{
				tmp->labelType = update;
				return SUCCESS;
			}		
		}
		tmp = tmp->next;
	}
	error_check("UNEXISTED");
	return ERROR;
}







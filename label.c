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

/*A function that print a label name, label value and his type*/
void print_label()
{
	labelPtr tmp;
	tmp = (labelPtr)malloc(sizeof(label));
	if(tmp == NULL)/*If is not have a label return error*/
	{
		error_check("ALLOCATE");
	}
	tmp = label_head;
	while(tmp != NULL)/*Loop that print the label as long as have a label*/
	{
		printf("\n%s, %d, ", tmp->labelName, tmp->labelValue);/*Print the label name and his value*/
		if(tmp->labelType == DATA_LABEL)/*If the label is data*/
			printf("data\n");/*Print the type-data*/
		if(tmp->labelType == ENTRY_LABEL)/*If the label is entry*/
			printf("entry\n");/*Print the type-entry*/
		if(tmp->labelType == EXTERN_LABEL)/*If the label is extern*/
			printf("extern\n");/*Print the type-extern*/
		if(tmp->labelType == CODE_LABEL)/*If the label is code*/
			printf("code\n");/*Print the type-code*/
		if(tmp->labelType == UNDEFINED_LABEL)/*If the label is not set*/
			printf("undefined\n");/*Print undefined*/
		tmp = tmp->next;/*Progress to the next node*/	
	}
}

/*A function that add the label to a linked list*/
void add_label(char * name, int value, int type)
{
	labelPtr tmp, newLabel;
	if (label_head == NULL)/*If the list is empty*/
	{	
		label_head = (labelPtr)malloc(sizeof(label));
		label_head->labelName = (char *)malloc(sizeof(name)*sizeof(char));
		if((label_head->labelName == NULL)||(label_head == NULL))/*If the name is empty-return error*/
		{
			error_check("ALLOCATE");
		}
		strcpy(label_head->labelName, name);/*Add the name to the labelNmae*/
		label_head->labelValue = value;/*Add the value to the labelValue*/
		label_head->labelType = type;/*Add the type to the labelType*/
		label_head->next = NULL;/*Add the pointer to the NULL*/
	}
	else/*If in the list have a parts*/
	{
		tmp = (labelPtr)malloc(sizeof(label));
		newLabel = (labelPtr)malloc(sizeof(label));
		if((tmp == NULL)||(newLabel == NULL))/*If the new label is empty-return error*/
		{
			error_check("ALLOCATE");
		}
		tmp = label_head;
		while(tmp->next != NULL)/*Loop that run by the end of the list*/
		{
			if(strcmp(tmp->labelName,name) == 0)/*If is not have the name-return error*/
			{
				error_check("EXISTED");
			}
			tmp = tmp->next;/*Progress to the next node*/
		}
		newLabel->labelName = (char *)malloc(sizeof(name)*sizeof(char));
		if (newLabel->labelName == NULL)/*If is not have the name-return error*/
		{
			error_check("ALLOCATE");
		}
		strcpy(newLabel->labelName, name);/*Add the name to the labelNmae*/
		newLabel->labelValue = value;/*Add the value to the labelValue*/
		newLabel->labelType = type;/*Add the type to the labelType*/
		newLabel->next = NULL;/*Add the pointer to the NULL*/
		tmp->next = newLabel;/*Progress to the next node*/
	}
}

/*A function get a anew label*/
void get_label(char *name, int feature, int featureType, labelPtr* label)
{
	if(*label == NULL)/*If the label is NULL-return error*/
	{
		error_check("ALLOCATE");
		return;
	}
	*label = label_head;
	while(*label != NULL)/*Al loop that run as long as the label equle to NULL*/
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

/*A function that update a new label*/
int update_label(int update, int updateType, int labelType, char *name)
{
	labelPtr tmp;
	tmp = (labelPtr)malloc(sizeof(label));
	if(tmp == NULL)/*If the tmp is empty-return error*/
	{
		error_check("ALLOCATE");
		return ERROR;
	}	
	tmp = label_head;
	while(tmp != NULL)/*Loop that run as long as the temp isn't equle to null*/
	{
		if((strcmp(tmp->labelName, name) == 0)||(strcmp(name, "ALL") == 0)&&(tmp->labelType == labelType))
		{
			if(updateType == LABEL_VALUE)
			{
				tmp->labelValue+= update;
				if (strcmp(tmp->labelName, name) == 0)				
					return SUCCESS;
			}
			if(updateType == LABEL_TYPE)
			{
				tmp->labelType = update;
				if (strcmp(tmp->labelName, name) == 0)				
					return SUCCESS;
			}		
		}
		tmp = tmp->next;
	}
	error_check("UNEXISTED");
	return ERROR;
}







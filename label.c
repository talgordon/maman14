#include "error.h"
#include "label.h"

int isreserved(char * word)
{
	if ((strcmp(word, "string") == 0 )|| (strcmp(word, "data") == 0) || (strcmp(word, "extern") == 0) || (strcmp(word, "entry") == 0))
		return 0;
	if ((strcmp(word, "r1") == 0) || (strcmp(word, "r2") == 0) || (strcmp(word, "r3") == 0) || (strcmp(word, "r4") == 0) || (strcmp(word, "r5") == 0) || (strcmp(word, "r6") == 0) || (strcmp(word, "r7") == 0))
		return 0;
	if ((strcmp(word, "mov") == 0) || (strcmp(word, "cmp") == 0) || (strcmp(word, "add") == 0) || (strcmp(word, "sub") == 0) || (strcmp(word, "lea") == 0) || (strcmp(word, "clr") == 0) || (strcmp(word, "not") == 0) || (strcmp(word, "inc") == 0) || (strcmp(word, "dec") == 0) || (strcmp(word, "jmp") == 0) || (strcmp(word, "bne") == 0) || (strcmp(word, "red") == 0) || (strcmp(word, "prn") == 0) || (strcmp(word, "jsr") == 0) || (strcmp(word, "rts") == 0) || (strcmp(word, "stop") == 0))
		return 0;
	return 1;
}
	
int isillegal(char * word)
{
	int i;
	for (i = 0; i<strlen(word); i++)
	{
		if ((!isalpha(word[i])) && (!isdigit(word[i])))
			return 0;
	} 
	return 1;
}
/*A function that print a label name, label value and his type*/
void print_label()
{
	labelPtr tmp;
	tmp = (labelPtr)malloc(sizeof(label));
	if(tmp == NULL)/*If is not have a label return error*/
	{
		add_error(ALLOCATE);
	}
	tmp = label_head;
	while(tmp != NULL)/*Loop that print the label as long as have a label*/
	{
		printf("\n%s, %d, ", tmp->labelName, tmp->labelValue);/*Print the label name and his value*/
		if(tmp->labelType == DATA_LABEL)/*If the label is data*/
			printf("data");/*Print the type-data*/
		if(tmp->labelType == CODE_LABEL)/*If the label is code*/
			printf("code");/*Print the type-code*/
		if(tmp->labelType == UNDEFINED_LABEL)/*If the label is not set*/
			printf("undefined");/*Print undefined*/
		if(tmp->labelLink == ENTRY_LABEL)/*If the label is entry*/
			printf(", entry\n");/*Print the type-entry*/
		if(tmp->labelLink == EXTERN_LABEL)/*If the label is extern*/
			printf(", extern\n");/*Print the type-extern*/
		if(tmp->labelLink == NOT_LINKED_LABEL)/*If the label is not set*/
			printf("\n");/*Print undefined*/
		tmp = tmp->next;/*Progress to the next node*/	
	}
}

/*A function that add the label to a linked list*/
void add_label(char * name, int value, int type, int link)
{
	labelPtr tmp, newLabel;	
	if (name[strlen(name)-1] == ':')
		name[strlen(name)-1] = '\0';
	printf("name is: %s\n", name);
	if (label_head == NULL)/*If the list is empty*/
	{	
		label_head = (labelPtr)malloc(sizeof(label));
		label_head->labelName = (char *)malloc(sizeof(name)*sizeof(char));
		if((label_head->labelName == NULL)||(label_head == NULL))/*If the name is empty-return error*/
		{
			add_error(ALLOCATE);
		}
		if (!isalpha(*name))
		{
			add_error(INVALID_LABEL_NAME);
			return;
		}
		if (isreserved(name) == 0)
		{
			add_error(RESERVED_LABEL_NAME);
			return;
		}
		if (strlen(name) > MAX_LABEL)
		{
			add_error(TOO_LONG_LABEL);
			return;
		}
		if (isillegal(name) == 0)
		{
			add_error(INVALID_LABEL_NAME);
			return;
		}
		strcpy(label_head->labelName, name);/*Add the name to the labelNmae*/
		label_head->labelValue = value;/*Add the value to the labelValue*/
		label_head->labelType = type;/*Add the type to the labelType*/
		label_head->labelLink = link;
		label_head->next = NULL;/*Add the pointer to the NULL*/
	}
	else/*If in the list have a parts*/
	{
		tmp = (labelPtr)malloc(sizeof(label));
		newLabel = (labelPtr)malloc(sizeof(label));
		if((tmp == NULL)||(newLabel == NULL))/*If the new label is empty-return error*/
		{
			add_error(ALLOCATE);
		}
		tmp = label_head;
		while(tmp->next != NULL)/*Loop that run by the end of the list*/
		{
			if(strcmp(tmp->labelName,name) == 0)/*If is not have the name-return error*/
			{
				add_error(MULTIPLE_LABEL);
			}
			tmp = tmp->next;/*Progress to the next node*/
		}
		newLabel->labelName = (char *)malloc(sizeof(name)*sizeof(char));
		if (newLabel->labelName == NULL)/*If is not have the name-return error*/
		{
			add_error(ALLOCATE);
		}
		if (!isalpha(*name))
		{
			add_error(INVALID_LABEL_NAME);
			return;
		}
		if (isreserved(name) == 0)
		{
			add_error(RESERVED_LABEL_NAME);
			return;
		}
		if (strlen(name) > MAX_LABEL)
		{
			add_error(TOO_LONG_LABEL);
			return;
		}
		if (isillegal(name) == 0)
		{
			add_error(INVALID_LABEL_NAME);
			return;
		}
		strcpy(newLabel->labelName, name);/*Add the name to the labelNmae*/
		newLabel->labelValue = value;/*Add the value to the labelValue*/
		newLabel->labelType = type;/*Add the type to the labelType*/
		newLabel->labelLink = link;
		newLabel->next = NULL;/*Add the pointer to the NULL*/
		tmp->next = newLabel;/*Progress to the next node*/
	}
}

/*A function get a anew label*/
void get_label(char *name, int feature, int featureType, labelPtr* label)
{
	if(*label == NULL)/*If the label is NULL-return error*/
	{
		add_error(ALLOCATE);
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
		if((featureType == LABEL_LINK) && (feature == (*label)->labelLink))
			return;
		*label = (*label)->next;
	}
	*label = NULL;
	add_error(UNEXISTED_LABEL);
}

/*A function that update a new label*/
int update_label(int update, int updateType, int labelID, int IDType, char *name)
{
	labelPtr tmp;
	tmp = (labelPtr)malloc(sizeof(label));
	if(tmp == NULL)/*If the tmp is empty-return error*/
	{
		add_error(ALLOCATE);
		return ERROR;
	}	
	tmp = label_head;
	while(tmp != NULL)/*Loop that run as long as the temp isn't equle to null*/
	{
		if ((strcmp(tmp->labelName, name) == 0)||((strcmp(name, "ALL") == 0) && (((IDType == LABEL_TYPE) && (labelID == tmp->labelType)) || ((IDType == LABEL_LINK) && (labelID == tmp->labelLink)))))
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
			if(updateType == LABEL_LINK)
			{
				tmp->labelLink = update;
				if (strcmp(tmp->labelName, name) == 0)				
					return SUCCESS;
			}			
		}
		tmp = tmp->next;
	}
	if (strcmp(name, "ALL") != 0)
		add_error(UNEXISTED_LABEL);
	return ERROR;
}


void add_extern(char * name, int value)
{
	externPtr tmp, newExtern;	
	printf("name is: %s\n", name);
	if (extern_head == NULL)/*If the list is empty*/
	{	
		extern_head = (externPtr)malloc(sizeof(externLabel));
		extern_head->externName = (char *)malloc(sizeof(name)*sizeof(char));
		if((extern_head->externName == NULL)||(extern_head == NULL))/*If the name is empty-return error*/
		{
			add_error(ALLOCATE);
		}
		strcpy(extern_head->externName, name);/*Add the name to the labelNmae*/
		extern_head->externValue = value;/*Add the value to the labelValue*/
		extern_head->next = NULL;/*Add the pointer to the NULL*/
	}
	else/*If in the list have a parts*/
	{
		tmp = (externPtr)malloc(sizeof(externLabel));
		newExtern = (externPtr)malloc(sizeof(externLabel));
		if((tmp == NULL)||(newExtern == NULL))/*If the new label is empty-return error*/
		{
			add_error(ALLOCATE);
		}
		tmp = extern_head;
		while(tmp->next != NULL)/*Loop that run by the end of the list*/
		{
			tmp = tmp->next;/*Progress to the next node*/
		}
		newExtern->externName = (char *)malloc(sizeof(name)*sizeof(char));
		if (newExtern->externName == NULL)/*If is not have the name-return error*/
		{
			add_error(ALLOCATE);
		}
		strcpy(newExtern->externName, name);/*Add the name to the labelNmae*/
		newExtern->externValue = value;/*Add the value to the labelValue*/
		newExtern->next = NULL;/*Add the pointer to the NULL*/
		tmp->next = newExtern;/*Progress to the next node*/
	}
}

void print_extern(FILE * fp)
{
	externPtr tmp;
	tmp = (externPtr)malloc(sizeof(externLabel));
	if(tmp == NULL)/*If is not have a label return error*/
	{
		add_error(ALLOCATE);
	}
	tmp = extern_head;
	while(tmp != NULL)/*Loop that print the label as long as have a label*/
	{
		fprintf(fp,"\n%s\t%04d", tmp->externName, tmp->externValue);/*Print the label name and his value*/
		tmp = tmp->next;/*Progress to the next node*/	
	}
}


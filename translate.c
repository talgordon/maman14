#include "error.h"
#include "analize_code_word.h"
#include "analize_input_line.h"

/*A function that adds a memory word to data image*/
int write_data_image(dataWord dWord)
{	
	memWordPtr tmp, newWord;
	if (dataHead == NULL)/*If the head is null*/
	{
		dataHead = (memWordPtr)malloc(sizeof(memWord));
		if (dataHead == NULL)/*Couldnt allocate space,error*/
		{
			add_error(ALLOCATE);
			return ERROR;
		}
		dataHead->word = dWord.data;/*Initializes the word*/
		dataHead->index = DC;/*Initializes the index*/
		DC++;
		dataHead->next = NULL;
		return SUCCESS;
	}
	else/*If the haed is not null*/
	{
		tmp = (memWordPtr)malloc(sizeof(memWord));
		newWord = (memWordPtr)malloc(sizeof(memWord));
		if((tmp == NULL)||(newWord == NULL))/*Couldnt allocate space,error*/
		{
			add_error(ALLOCATE);
			return ERROR;
		}
		tmp = dataHead;
		while(tmp->next != NULL)
			tmp = tmp->next;

		newWord->word = dWord.data;/*Initializes the word*/
		newWord->index = DC;/*Initializes the index*/
		DC++;
		newWord->next = NULL;
		tmp->next = newWord;
		return SUCCESS;
	}
}

/*A function that adds a memory word to code image*/
int write_code_image(wordPtr ptr, int type)
{
	switch (type)/*Check the type*/
	{
		case (CODE_WORD):/*If it is code word-initializes in buffer as per the data*/
		{
			buffer[IC] = ptr.codeWordPtr->opcode;
			buffer[IC] = (buffer[IC]<<4) + ptr.codeWordPtr->src;
			buffer[IC] = (buffer[IC]<<4) + ptr.codeWordPtr->dst;
			buffer[IC] = (buffer[IC]<<3) + ptr.codeWordPtr->ARE;
			break;
		}
		case (DATA_WORD):/*If it is data word-initializes in buffer as per the data*/
		{
			buffer[IC] = ptr.dataWordPtr->data;
			buffer[IC] = (buffer[IC]<<3) + ptr.dataWordPtr->ARE;
			break;
		}
		case (DATA_REG_WORD):/*If it is data reg word-initializes in buffer as per the data*/
		{
			buffer[IC] = ptr.regWordPtr->rest;
			buffer[IC] = (buffer[IC]<<3) + ptr.regWordPtr->srcReg;
			buffer[IC] = (buffer[IC]<<3) + ptr.regWordPtr->dstReg;
			buffer[IC] = (buffer[IC]<<3) + ptr.regWordPtr->ARE;
			break;
		}	
	}
	return SUCCESS;
}

/*A functio that print a nenory word*/
int print_mem(FILE * fp)
{
	memWordPtr tmp;
	int i;
	for (i = 100; i < IC; i++)
	{
		fprintf(fp,"\n%04d\t%05o", i, buffer[i]);
	}
	tmp = (memWordPtr)malloc(sizeof(memWord));
	if(tmp == NULL)
	{
		add_error(ALLOCATE);
		return ERROR;
	}
	tmp = dataHead;
	while(tmp != NULL)
	{
		fprintf(fp,"\n%04d\t%05o", tmp->index+IC, tmp->word);
		tmp = tmp->next;
	}
	printf("\n");
	return SUCCESS;
}


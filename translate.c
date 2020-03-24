#include "error.h"
#include "analize_code_word.h"
#include "analize_input_line.h"
int write_data_image(dataWord dWord)
{	
	memWordPtr tmp, newWord;
	printf("in data_image\n");
	if (dataHead == NULL)
	{
		printf("head is null\n");
		dataHead = (memWordPtr)malloc(sizeof(memWord));
		if (dataHead == NULL)
		{
			add_error(ALLOCATE);
			return ERROR;
		}
		dataHead->word = dWord.data;
		dataHead->index = DC;
		DC++;
		printf("DC:%d, data:%d\n", DC, dWord.data);
		dataHead->next = NULL;
		return SUCCESS;
	}
	else
	{
		printf("head is not null\n");
		tmp = (memWordPtr)malloc(sizeof(memWord));
		newWord = (memWordPtr)malloc(sizeof(memWord));
		if((tmp == NULL)||(newWord == NULL))
		{
			add_error(ALLOCATE);
			return ERROR;
		}
		tmp = dataHead;
		while(tmp->next != NULL)
			tmp = tmp->next;
		printf("finish while\n");
		newWord->word = dWord.data;
		newWord->index = DC;
		DC++;
		printf("DC:%d, data:%d\n", DC, dWord.data);
		newWord->next = NULL;
		tmp->next = newWord;
		return SUCCESS;
	}
}

int write_code_image(wordPtr ptr, int type)
{
	switch (type)
	{
		case (CODE_WORD):
		{
			printf("case CODE_WORD. opcode:%d, src:%d, dst:%d, ARE:%d\n",ptr.codeWordPtr->opcode, ptr.codeWordPtr->src, ptr.codeWordPtr->dst, ptr.codeWordPtr->ARE );
			buffer[IC] = ptr.codeWordPtr->opcode;
			buffer[IC] = (buffer[IC]<<4) + ptr.codeWordPtr->src;
			buffer[IC] = (buffer[IC]<<4) + ptr.codeWordPtr->dst;
			buffer[IC] = (buffer[IC]<<3) + ptr.codeWordPtr->ARE;
			printf("buffer[IC]:%05o, IC:%d\n", buffer[IC], IC);
			break;
		}
		case (DATA_WORD):
		{
			printf("case DATA_WORD. data:%d, ARE:%d\n",ptr.dataWordPtr->data, ptr.dataWordPtr->ARE);
			buffer[IC] = ptr.dataWordPtr->data;
			buffer[IC] = (buffer[IC]<<3) + ptr.dataWordPtr->ARE;
			printf("buffer[IC]:%o\n", buffer[IC]);
			break;
		}
		case (DATA_REG_WORD):
		{
			printf("case DATA_REG_WORD. rest:%d, src:%d, dst:%d,ARE:%d\n",ptr.regWordPtr->rest,ptr.regWordPtr->srcReg, ptr.regWordPtr->dstReg, ptr.regWordPtr->ARE);
			buffer[IC] = ptr.regWordPtr->rest;
			buffer[IC] = (buffer[IC]<<3) + ptr.regWordPtr->srcReg;
			buffer[IC] = (buffer[IC]<<3) + ptr.regWordPtr->dstReg;
			buffer[IC] = (buffer[IC]<<3) + ptr.regWordPtr->ARE;
			printf("buffer[IC]:%o\n", buffer[IC]);
			break;
		}	
	}
	return SUCCESS;
}


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


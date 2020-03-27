#include "error.h"
#include "analize_code_word.h"
#include "analize_input_line.h"

/*A function that adds a memory word to data image*/
void write_data_image(dataWord dWord)
{	
	memWordPtr tmp, newWord;
	if (data_head == NULL)/*If the head is null*/
	{
		data_head = (memWordPtr)malloc(sizeof(memWord));
		if (data_head == NULL)/*Couldnt allocate space,error*/
		{
			add_error(ALLOCATE);
			return;
		}
		data_head->word = dWord.data;/*Initializes the word*/
		data_head->index = DC;/*Initializes the index*/
		DC++;
		data_head->next = NULL;
	}
	else/*If the haed is not null*/
	{
		tmp = (memWordPtr)malloc(sizeof(memWord));
		newWord = (memWordPtr)malloc(sizeof(memWord));
		if((tmp == NULL)||(newWord == NULL))/*Couldnt allocate space,error*/
		{
			add_error(ALLOCATE);
			return;
		}
		tmp = data_head;
		while(tmp->next != NULL)
			tmp = tmp->next;

		newWord->word = dWord.data;/*Initializes the word*/
		newWord->index = DC;/*Initializes the index*/
		DC++;
		newWord->next = NULL;
		tmp->next = newWord;
	}
}

/*A function that adds a memory word to code image*/
void write_code_image(wordPtr ptr, int type)
{
	switch (type)/*Check the type*/
	{
		case (CODE_WORD):/*If it is code word-initializes in buffer as per the data*/
		{
			buffer[IC] = ptr.codeWordPtr->opcode;
			buffer[IC] = (buffer[IC]<<SRC_CODE_LENGTH) + ptr.codeWordPtr->src;
			buffer[IC] = (buffer[IC]<<DST_CODE_LENGTH) + ptr.codeWordPtr->dst;
			buffer[IC] = (buffer[IC]<<ARE_LENGTH) + ptr.codeWordPtr->ARE;
			break;
		}
		case (DATA_WORD):/*If it is data word-initializes in buffer as per the data*/
		{
			buffer[IC] = ptr.dataWordPtr->data;
			buffer[IC] = (buffer[IC]<<ARE_LENGTH) + ptr.dataWordPtr->ARE;
			break;
		}
		case (DATA_REG_WORD):/*If it is data reg word-initializes in buffer as per the data*/
		{
			buffer[IC] = ptr.regWordPtr->rest;
			buffer[IC] = (buffer[IC]<<SRC_DATA_LENGTH) + ptr.regWordPtr->srcReg;
			buffer[IC] = (buffer[IC]<<DST_DATA_LENGTH) + ptr.regWordPtr->dstReg;
			buffer[IC] = (buffer[IC]<<ARE_LENGTH) + ptr.regWordPtr->ARE;
			break;
		}	
	}
}

/*A functio that print a nenory word*/
void print_mem(FILE * fp)
{
	memWordPtr tmp;
	int i;
	for (i = 100; i < IC; i++)/*Print the word*/
	{
		fprintf(fp,"\n%04d\t%05o", i, buffer[i]);
	}
	tmp = (memWordPtr)malloc(sizeof(memWord));
	if(tmp == NULL)/*If is not can allocated*/
	{
		add_error(ALLOCATE);
		return;
	}
	tmp = data_head;
	while(tmp != NULL)/*Print*/
	{
		fprintf(fp,"\n%04d\t%05o", tmp->index+IC, tmp->word);
		tmp = tmp->next;
	}
	printf("\n");
	free(tmp);/*Free the word*/

}


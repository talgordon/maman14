#include "binary.c"
#include "error.c"
#include "label.c"
#define SUCCESS 0
#define ERROR 1
enum types{CODE_WORD, DATA_WORD, DATA_REG_WORD};
int DC, IC;
memWordPtr dataHead;

int buffer[4096];

int write_data_image(dataWord dWord)
{	
	memWordPtr tmp, newWord;
	if (dataHead == NULL)
	{
		dataHead = (memWordPtr)malloc(sizeof(memWord));
		if (dataHead == NULL)
		{
			error_check("ALLOCATE");
			return ERROR;
		}
		dataHead->word = dWord.data;
		dataHead->index = DC;
		DC++;
		dataHead->next = NULL;
		return SUCCESS;
	}
	else
	{
		tmp = (memWordPtr)malloc(sizeof(memWord));
		newWord = (memWordPtr)malloc(sizeof(memWord));
		if((tmp == NULL)||(newWord == NULL))
		{
			error_check("ALLOCATE");
			return ERROR;
		}
		tmp = dataHead;
		while(tmp->next != NULL)
			tmp = tmp->next;
		newWord->word = dWord.data;
		newWord->index = DC;
		DC++;
		newWord->next = NULL;
		tmp->next = newWord;
		return SUCCESS;
	}
}

int write_code_image(wordPtr ptr, int type)
{
	IC = 0;
	switch (type)
	{
		case (CODE_WORD):
		{
			buffer[IC] = ptr.codeWordPtr->opcode;
			buffer[IC] = (buffer[IC]<<4) + ptr.codeWordPtr->src;
			buffer[IC] = (buffer[IC]<<4) + ptr.codeWordPtr->dst;
			buffer[IC] = (buffer[IC]<<3) + ptr.codeWordPtr->ARE;
			IC++;
			break;
		}
		case (DATA_WORD):
		{
			
			buffer[IC] = ptr.dataWordPtr->data;
			buffer[IC] = (buffer[IC]<<3) + ptr.dataWordPtr->ARE;
			IC++;
			break;
		}
		case (DATA_REG_WORD):
		{
			buffer[IC] = ptr.regWordPtr->rest;
			buffer[IC] = (buffer[IC]<<3) + ptr.regWordPtr->srcReg;
			buffer[IC] = (buffer[IC]<<3) + ptr.regWordPtr->dstReg;
			buffer[IC] = (buffer[IC]<<3) + ptr.regWordPtr->ARE;
			IC++;
			break;
		}	
	}
	return SUCCESS;
}


int print_mem()
{
	memWordPtr tmp;
	int i;
	for (i = 100; i < (IC + 100); i++)
	{
		printf("\n%d\t%o", i, buffer[i-100]);
	}
	tmp = (memWordPtr)malloc(sizeof(label));
	if(tmp == NULL)
	{
		error_check("ALLOCATE");
		return ERROR;
	}
	tmp = dataHead;
	while(tmp != NULL)
	{
		printf("\n%d\t%o", tmp->index, tmp->word);
		tmp = tmp->next;
	}
	printf("\n");
	return SUCCESS;
}

int main()
{
	wordPtr ptr;
	dataWord word;
	codeWord wordC;

	word.data = 9;
	write_data_image(word);
	word.data = two_complement(-100);
	write_data_image(word);
	word.data = 'a';
	write_data_image(word);

	wordC.opcode = 2;
	wordC.src = 4;
	wordC.dst = 2;
	wordC.ARE = 4;
	ptr.codeWordPtr = &wordC;
	write_code_image(ptr, CODE);
	print_mem();
	return 0;	
}

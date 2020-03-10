#include "translate.h"
#inclulde "analize_input_line.h"
#define MAX_WORDS 4096
#define A 4
#define R 2
#define E 1
#define IMMEDIATE 1
#define DIRECT 2
#define INDIRECT_REGISTER 4
#define DIRECT_REGISTER 8

const char * opcodeTable[16] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};
/**addressMethod addressTable[16];
addressTable[0]->src = 15;
addressTable[0]->dst = 7;
addressTable[1].src = 15; 
addressTable[1].dst = 15; 
addressTable[2].src = 15;
addressTable[2].dst = 7;
addressTable[3].src = 15;
addressTable[3].dst = 7;
addressTable[4].src = 4;
addressTable[4].dst = 7; 
addressTable[5].src = 0;
addressTable[5].dst = 7; 
addressTable[6].src = 0;
addressTable[6].dst = 7; 
addressTable[7].src = 0;
addressTable[7].dst = 7; 
addressTable[8].src = 0;
addressTable[8].dst = 7; 
addressTable[9].src = 0;
addressTable[9].dst = 6; 
addressTable[10].src = 0;
addressTable[10].dst = 6;    
addressTable[11].src = 0;
addressTable[11].dst = 7;  
addressTable[12].src = 0;
addressTable[12].dst = 15; 
addressTable[13].src = 0;
addressTable[13].dst = 6;  
addressTable[14].src = 0;
addressTable[14].dst = 0;
addressTable[15].src = 0;
addressTable[15].dst = 0; **/

int find_opcode(char * opcode)
{
	int i;
	
	for(i = 0; i<16; i++)
	{
		if (strcmp(opcode, opcodeTable[i]) == 0)
			return i;
	}
	return -1;
}

int translate_code()
{
	codeWord firstWord;
	/**get the opcode - first 4 bits in the word**/
	char *word;
	int opcode;
	if (getWord(word)!=OTHER)
		return ERROR;
	if ((opcode = find_opcode(word)) < 0)
		error_check("OPCODE");
	else
		firstWord.opcode = opcode;


	/**get the address method - next 8 bits in the word**/
	char * srcName;
	char * dstName;
	int srcType;
	int dstType;
	srcType = 0;
	dstType = 0;
	get_operands(&srcName, &srcType, &dstName, &dstType);

	int numOfOp_table, numOfOp_line;
	numOfOp_table = 0;
	numOfOp_line = 0;
	if (addressTable.src != 0)
		numOfOp_table++;
	if (addressTable.dst != 0)
		numOfOp_table++;
	if (srcType != 0)
		numOfOp_line++;
	if (dstType != 0)
		numOfOp_line++;
	if(numOfOp_table != numOfOp_line)
		error_check("NUM_OF_OPERANDES");

	if (!(srcType&addressTable[firstWord.opcode].src) && (dstType&addressTable[firstWord.opcode].dst))
		error_check("INVALID_OPERANDS");
	else
	{
		firstWord.src = srcType;
		firstWord.dst = dstType;
	}
		
		
	/**get the ARE field - last 4 bits in the word**/
	firstWord.ARE = A;
	
}

int finish_translate(char *line)
{
	char * srcName;
	char * dstName;
	int srcType;
	int dstType;
	srcType = 0;
	dstType = 0;
	get_operands(&srcName, &srcType, &dstName, &dstType);
	/**get the info words, one, two or non at all**/	
	if((srcType == IMMEDIATE) || (srcType == DIRECT))
	{
		infoWordData srcInfo;
		if(srcType == IMMEDIATE)
		{
			srcInfo.data = two_complement(atoi(srcName));
			srcInfo.ARE = A;
		}
		else
		{
			labelPtr label;
			label = (labelPtr)malloc(sizeof(label));
			get_label(srcName, 0, 0, label);
			srcInfo.data = label->value;
			if(label->type == EXTERN)
				srcInfo.ARE = E;
			else
				srcInfo.ARE = R;
		}
	}
	else
	{
		infoWordReg srcInfoReg;
		srcInfoReg.srcReg = atoi(srcName);
		srcInfoReg.ARE = A;
		if ((dstType == INDIRECT_REGISTER) || (dstType == DIRECT_REGISTER))
			srcInfoReg.dstReg = atoi(dstName);
		else
			srcInfoReg.dstReg = 0;
		srcInfoReg.rest = 0;
	}

	if((dstType == IMMEDIATE) || (dstType == DIRECT))
	{
		infoWordData dstInfo;
		if(dstType == IMMEDIATE)
		{
			dstInfo.data = two_complement(atoi(dstName));
			dstInfo.ARE = A;
		}
		else
		{
			labelPtr label;
			label = (labelPtr)malloc(sizeof(label));
			get_label(dstName, 0, 0, label);
			dstInfo.data = label->value;
			if(label.type == EXTERN)
				dstInfo.ARE = E;
			else
				dstInfo.ARE = R;
		}
	}
	else
	{
		infoWordReg dstInfoReg;
		dstInfoReg.dstReg = atoi(dstName);
		dstInfoReg.ARE = A;
		dstInfoReg.srcReg = 0;
		dstInfoReg.rest = 0;
	}
			
	
}

int translate_data(int type, char * line)
{
	dataWord word;
	int num, c;
	if (type == DATA)
	{
		while((num = get_data(line))!=EOF)
		{
			word.data = two_comlement(num);
			write_data_image(word);
		}
	}

	if(type == STRING)
	{
		while((c = *line) != EOF)
		{
			word.data = c;
			write_data_image(word);
		}
		word.data = 0;
		write_data_image(word);
	}
	return 0;
}

#include "analize_code_word.h"
#include "analize_input_line.h"
#include "error.h"
#include "label.h"
#define MAX_WORDS 4096
#define A 4
#define R 2
#define E 1
#define IMMEDIATE 1
#define DIRECT 2
#define INDIRECT_REGISTER 4
#define DIRECT_REGISTER 8



int main()
{
	wordPtr wordP;
	int opcode, srcType, dstType;
	char * line;
	line = (char *)malloc(sizeof(char)*MAX_WORD);
	strcpy(line, "	#48, 	*r6");	
	opcode = find_opcode("add");
	srcType = 2;
	dstType = 4;
	translate_code(wordP, opcode, srcType, dstType);

	finish_translate(line, wordP);

	strcpy(line, "	abcd");
	translate_data(STRING, line);
	print_mem();
	return 0;	
}
const char * opcodeTable[16] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};
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

int translate_code(wordPtr wPtr, int opcode, int srcType, int dstType)
{
	codeWord firstWord;
	int numOfOp_table, numOfOp_line;
	/**get the opcode - first 4 bits in the word**/
	firstWord.opcode = opcode;

	/**get the address method - next 8 bits in the word**/
	
	numOfOp_table = 0;
	numOfOp_line = 0;
	if (addressTable->src != 0)
		numOfOp_table++;
	if (addressTable->dst != 0)
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
	wPtr.codeWordPtr = &firstWord;
	write_code_image(wPtr, CODE_WORD);
}

int finish_translate(char *line, wordPtr wPtr)
{
	char * srcName;
	char * dstName;
	int srcType;
	int dstType;
	srcType = 0;
	dstType = 0;
	get_operands(line, &srcName, &srcType, &dstName, &dstType);
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
			get_label(srcName, 0, 0, &label);
			srcInfo.data = label->labelValue;
			if(label->labelType == EXTERN)
				srcInfo.ARE = E;
			else
				srcInfo.ARE = R;
		}
		wPtr.dataWordPtr = &srcInfo;
		write_code_image(wPtr, DATA_WORD);
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
		wPtr.regWordPtr = &srcInfoReg;
		write_code_image(wPtr, DATA_REG_WORD);
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
			get_label(dstName, 0, 0, &label);
			dstInfo.data = label->labelValue;
			if(label->labelType == EXTERN)
				dstInfo.ARE = E;
			else
				dstInfo.ARE = R;
		}
		wPtr.dataWordPtr = &dstInfo;
		write_code_image(wPtr, DATA_WORD);
	}
	else
	{
		infoWordReg dstInfoReg;
		dstInfoReg.dstReg = atoi(dstName);
		dstInfoReg.ARE = A;
		dstInfoReg.srcReg = 0;
		dstInfoReg.rest = 0;
		wPtr.regWordPtr = &dstInfoReg;
		write_code_image(wPtr, DATA_REG_WORD);
	}
			
	
}

int translate_data(int type, char * line)
{
	dataWord word;
	int num, c;
	if (type == DATA)
	{
		while((num = get_data(&line))!=EOF)
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

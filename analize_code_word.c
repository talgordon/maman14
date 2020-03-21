#include "analize_code_word.h"
#include "analize_input_line.h"
#include "error.h"
#include "label.h"


const char * opcodeTable[16] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};
int find_opcode(char * opcode)
{
	int i;
	printf("in fine_opcode, opcode:%s\n", opcode);
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
	get_operand(line, &srcType, &dstType, &srcName, &dstName, 2);
	/**get the info words, one, two or non at all**/	
	if(dstType == 0)
	{
		return 0;
	}
	L++;
	if((srcType == IMMEDIATE) || (srcType == DIRECT))
	{
		infoWordData srcInfo;
		L++;
		if(srcType == IMMEDIATE)
		{
			srcInfo.data = two_complement(atoi(srcName));
			srcInfo.ARE = A;
		}
		else/*direct*/
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
		{
			srcInfoReg.dstReg = 0;
			L++;
		}
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
	int c;
	int num;
	if (type == DATA)
	{
		printf("case DATA\n");
		while((num = get_data(&line))!= EOF)
		{
			
			word.data = two_complement(num);
			printf("call write_data_image with %d\n", num);
			write_data_image(word);
			printf("finish data_image\n");
		}
	}

	if(type == STRING)
	{
		printf("case STRING\n");
		while((c = *line) != '\n')
		{
			word.data = c;
			printf("call write_data_image with %c\n", c);
			write_data_image(word);
			line++;
		}
		word.data = 0;
		write_data_image(word);
	}
	return 0;
}
int two_complement(int num)
{
	return (~num)+1;
}

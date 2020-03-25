#include "analize_code_word.h"
#include "analize_input_line.h"
#include "error.h"
#include "label.h"

/*An array with the opcode name*/
const char * opcodeTable[16] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};

/*A function that find the opcode in the array*/
int find_opcode(char * opcode)
{
	int i;
	for(i = 0; i<16; i++)/*A loop that run on the array and compares between the opcode she accepts and the place in opcodeTable*/
	{
		if (strcmp(opcode, opcodeTable[i]) == 0)
			return i;
	}
	return -1;
}

/*A function that encodes insruction to binary memory word*/
int translate_code(wordPtr wPtr, int opcode, int srcType, int dstType)
{
	codeWord * firstWord;
	int numOfOp_table, numOfOp_line;
	firstWord = (codeWord *)malloc(sizeof(codeWord));
	/**get the opcode - first 4 bits in the word**/
	firstWord->opcode = opcode;

	/**get the address method - next 8 bits in the word**/
	
	numOfOp_table = 0;
	numOfOp_line = 0;
	if (addressTable[opcode].src != 0)
	{
		numOfOp_table++;
	}
	if (addressTable[opcode].dst != 0)
		numOfOp_table++;
	if (srcType != 0)
		numOfOp_line++;
	if (dstType != 0)
		numOfOp_line++;

	if(numOfOp_table > numOfOp_line)
	{
		add_error(TOO_FEW_OPERANDS);
	}
	if(numOfOp_table < numOfOp_line)
	{
		add_error(TOO_MANY_OPERANDS);
	}
	if (srcType&addressTable[firstWord->opcode].src == 0)	
	{
		add_error(INVALID_SRC_TYPE);
	}	
	if (dstType&addressTable[firstWord->opcode].dst == 0)
	{
		add_error(INVALID_DST_TYPE);
	}
	firstWord->src = srcType;
	firstWord->dst = dstType;
		
	/**get the ARE field - last 4 bits in the word**/
	firstWord->ARE = A;
	wPtr.codeWordPtr = firstWord;
	write_code_image(wPtr, CODE_WORD);
}

int finish_translate(char *line, wordPtr wPtr)
{
	char * srcName;
	char * dstName;
	int srcType;
	int dstType;
	srcName = (char *)malloc(sizeof(char)*MAX_WORD);
	dstName = (char *)malloc(sizeof(char)*MAX_WORD);
	srcType = 0;
	dstType = 0;

	get_operand(line, &srcType, &dstType, &srcName, &dstName, 2);
	/**get the info words, one, two or non at all**/	
	if(dstType == 0)/*If is not have oparends*/
	{
		return 0;
	}
	if((srcType == IMMEDIATE) || (srcType == DIRECT))/*If src is IMMEDIATE OR DIRECT*/
	{
		infoWordData srcInfo;
		if(srcType == IMMEDIATE)/*If src is IMMEDIATE*/
		{
			srcInfo.data = atoi(srcName);
			srcInfo.ARE = A;
		}
		else/*If src is direct*/
		{
			labelPtr label;
			label = (labelPtr)malloc(sizeof(label));
			get_label(srcName, 0, 0, &label);
			if(label->labelLink == EXTERN_LABEL)
			{			
				srcInfo.ARE = E;
				srcInfo.data = 0;
				add_extern(label->labelName, IC);
			}
			else
			{
				srcInfo.ARE = R;
				srcInfo.data = label->labelValue;
			}
		}
		wPtr.dataWordPtr = &srcInfo;
		write_code_image(wPtr, DATA_WORD);
		IC++;
	}
	else 
	{
		if (((srcType == DIRECT_REGISTER) || (srcType == INDIRECT_REGISTER)))/*If src is DIRECT_REG OR INDIRECT_REG*/
		{
			infoWordReg srcInfoReg;
			srcInfoReg.srcReg = atoi(srcName);
			srcInfoReg.ARE = A;
			if ((dstType == INDIRECT_REGISTER) || (dstType == DIRECT_REGISTER))
				srcInfoReg.dstReg = atoi(dstName);
			else
			{
				srcInfoReg.dstReg = 0;
			}
			srcInfoReg.rest = 0;
			wPtr.regWordPtr = &srcInfoReg;
		
			write_code_image(wPtr, DATA_REG_WORD);
			IC++;
		}
	}

	if((dstType == IMMEDIATE) || (dstType == DIRECT))
	{
		infoWordData dstInfo;
		if(dstType == IMMEDIATE)/*If is immideate*/
		{
			dstInfo.data = atoi(dstName);
			dstInfo.ARE = A;
		}
		else/*If is direct*/
		{
			labelPtr label;
			label = (labelPtr)malloc(sizeof(label));
			get_label(dstName, 0, 0, &label);
			
			if(label->labelLink == EXTERN_LABEL)
			{
				dstInfo.ARE = E;
				dstInfo.data = 0;
				add_extern(label->labelName, IC);
			}
			else
			{
				dstInfo.ARE = R;
				dstInfo.data = label->labelValue;
			}
		}
		wPtr.dataWordPtr = &dstInfo;
		
		write_code_image(wPtr, DATA_WORD);
		IC++;
	}
	else
		if (!(((srcType == DIRECT_REGISTER) || (srcType == INDIRECT_REGISTER)) && ((dstType == DIRECT_REGISTER) || (dstType == INDIRECT_REGISTER))))/*If is reg*/
		{
			infoWordReg dstInfoReg;
			dstInfoReg.dstReg = atoi(dstName);
			dstInfoReg.ARE = A;
			dstInfoReg.srcReg = 0;
			dstInfoReg.rest = 0;
			wPtr.regWordPtr = &dstInfoReg;
			
			write_code_image(wPtr, DATA_REG_WORD);
			IC++;
		}
			
	
}

/*A function that encodes guidance to binary memory word*/
int translate_data(int type, char * line)
{
	dataWord word;
	int c;
	int num;
	if (type == DATA)/*If is data*/
	{
		skip_spaces(&line);
		if (*line == '\n')/*If the line is empty, error*/
		{
			add_error(MISSING_DATA);
			return 0;
		}
		while((num = get_data(&line))!= EOF)
		{
			
			word.data = num;
			write_data_image(word);
		}
	}

	if(type == STRING)/*If is string*/
	{
		skip_spaces(&line);
		if (*line == '\n')/*If the line is empty, error*/
		{
			add_error(MISSING_DATA);
			return 0;
		}
		line++;
		while(((c = *line) != '\n')&&(c != '"'))
		{
			word.data = c;
			write_data_image(word);
			line++;
		}
		word.data = 0;
		write_data_image(word);
	}
	return 0;
}

/*A function that encodes a number using the two complement method*/
int two_complement(int num)
{
	return (~num)+1;
}

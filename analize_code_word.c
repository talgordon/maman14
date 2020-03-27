#include "analize_code_word.h"
#include "analize_input_line.h"
#include "error.h"
#include "label.h"

/*An array with the opcode name*/
const char * opcodeTable[NUM_OF_OPCODE] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};

/*A function that find the opcode in the array*/
int find_opcode(char * opcode)
{
	int i;
	for(i = 0; i<NUM_OF_OPCODE; i++)/*A loop that run on the array and compares between the opcode she accepts and the place in opcodeTable*/
	{
		if (strcmp(opcode, opcodeTable[i]) == 0)
			return i;
	}
	return ERROR;
}

/*A function that encodes insruction to binary memory word*/
void translate_code(wordPtr wPtr, int opcode, int srcType, int dstType)
{
	codeWord * firstWord;
	int numOfOp_table, numOfOp_line;
	firstWord = (codeWord *)malloc(sizeof(codeWord));
	/**get the opcode - first 4 bits in the word**/
	firstWord->opcode = opcode;
	/**get the address method - next 8 bits in the word**/
	
	numOfOp_table = 0;
	numOfOp_line = 0;
	if (addressTable[opcode].src != NO_OPERAND)
	{
		numOfOp_table++;
	}
	if (addressTable[opcode].dst != NO_OPERAND)
		numOfOp_table++;
	if (srcType != NO_OPERAND)
		numOfOp_line++;
	if (dstType != NO_OPERAND)
		numOfOp_line++;

	if(numOfOp_table > numOfOp_line)
	{
		add_error(TOO_FEW_OPERANDS);
	}
	if(numOfOp_table < numOfOp_line)
	{
		add_error(TOO_MANY_OPERANDS);
	}
	if (srcType&addressTable[firstWord->opcode].src == IS_FALSE)	
	{
		add_error(INVALID_SRC_TYPE);
	}	
	if (dstType&addressTable[firstWord->opcode].dst == IS_FALSE)
	{
		add_error(INVALID_DST_TYPE);
	}
	firstWord->src = srcType;
	firstWord->dst = dstType;
		
	/**get the ARE field - last 4 bits in the word**/
	firstWord->ARE = A;
	wPtr.codeWordPtr = firstWord;
	write_code_image(wPtr, CODE_WORD);
	free(firstWord);
}

void finish_translate(char *line, wordPtr wPtr)
{
	char * srcName;
	char * dstName;
	int srcType;
	int dstType;
	srcName = (char *)malloc(sizeof(char)*MAX_WORD);
	dstName = (char *)malloc(sizeof(char)*MAX_WORD);
	srcType = 0;
	dstType = 0;

	get_operand(line, &srcType, &dstType, &srcName, &dstName, SECOND);
	/**get the info words, one, two or non at all**/	
	if(dstType == NO_OPERAND)/*If is not have oparends*/
	{
		free(srcName);
		free(dstName);
		return;
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
			label = get_label(srcName, NOTHING, NOTHING, label);
			if(label->labelLink == EXTERN_LABEL)
			{			
				srcInfo.ARE = E;
				srcInfo.data = EMPTY;
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
				srcInfoReg.dstReg = EMPTY;
			}
			srcInfoReg.rest = EMPTY;
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
			label = get_label(dstName, NOTHING, NOTHING, label);
			if(label->labelLink == EXTERN_LABEL)
			{
				dstInfo.ARE = E;
				dstInfo.data = EMPTY;
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
			dstInfoReg.srcReg = EMPTY;
			dstInfoReg.rest = EMPTY;
			wPtr.regWordPtr = &dstInfoReg;
			
			write_code_image(wPtr, DATA_REG_WORD);
			IC++;
		}
	free(srcName);
	free(dstName);
			
	
}

/*A function that encodes guidance to binary memory word*/
void translate_data(int type, char * line)
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
			return;
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
			return;
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
}


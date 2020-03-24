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
	printf("numOfOp_table:%d, numOfOp_line:%d\n",numOfOp_table , numOfOp_line);
	if(numOfOp_table > numOfOp_line)
	{
		printf("too few\n");
		add_error(TOO_FEW_OPERANDS);
	}
	if(numOfOp_table < numOfOp_line)
	{
		printf("too many\n");
		add_error(TOO_MANY_OPERANDS);
	}
	if (srcType&addressTable[firstWord.opcode].src == 0)	
	{
		add_error(INVALID_SRC_TYPE);
		printf("case src\n");	
	}	
	if (dstType&addressTable[firstWord.opcode].dst == 0)
	{
		add_error(INVALID_DST_TYPE);
		printf("case dst\n");	
	}
	printf("src:%d, dst:%d\n", srcType, dstType);
	firstWord.src = srcType;
	firstWord.dst = dstType;
		
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
	srcName = (char *)malloc(sizeof(char)*MAX_WORD);
	dstName = (char *)malloc(sizeof(char)*MAX_WORD);
	srcType = 0;
	dstType = 0;
	printf("in finish translate, line:%s\n", line);
	get_operand(line, &srcType, &dstType, &srcName, &dstName, 2);
	printf("in finish translate, after get operands- srcType:%d, dstType:%d, srcName:%s, dstName:%s\n", srcType, dstType, srcName, dstName);
	/**get the info words, one, two or non at all**/	
	if(dstType == 0)
	{
		printf("no operands\n");
		return 0;
	}
	if((srcType == IMMEDIATE) || (srcType == DIRECT))
	{
		infoWordData srcInfo;
		printf("src is IMMEDIATE OR DIRECT\n");
		if(srcType == IMMEDIATE)
		{
			printf("src is IMMEDIATE\n");
			srcInfo.data = atoi(srcName);
			srcInfo.ARE = A;
			printf("finish case IMMEDIATE\n");
		}
		else/*direct*/
		{
			labelPtr label;
			printf("src is DIRECT\n");
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
			printf("finish case DIRECT\n");
		}
		wPtr.dataWordPtr = &srcInfo;
		printf("call to write code image with:data=%d, ARE=%d\n", wPtr.dataWordPtr->data, wPtr.dataWordPtr->ARE);
		write_code_image(wPtr, DATA_WORD);
		IC++;
		printf("finish write_code_image\n");
	}
	else 
	{
		if (((srcType == DIRECT_REGISTER) || (srcType == INDIRECT_REGISTER)))
		{
			infoWordReg srcInfoReg;
			printf("src is DIRECT_REG OR INDIRECT_REG\n");
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
			printf("call to write code image with:srcType=%d,dstType=%d, ARE=%d, rest=%d\n", wPtr.regWordPtr->srcReg, wPtr.regWordPtr->dstReg, wPtr.regWordPtr->ARE, wPtr.regWordPtr->rest);
			write_code_image(wPtr, DATA_REG_WORD);
			IC++;
			printf("finish write_code_image\n");
		}
	}
	printf("dstType:%d\n", dstType);
	if((dstType == IMMEDIATE) || (dstType == DIRECT))
	{
		infoWordData dstInfo;
		if(dstType == IMMEDIATE)
		{
			printf("case immideate\n");
			dstInfo.data = atoi(dstName);
			dstInfo.ARE = A;
			printf("finish case immidiate\n");
		}
		else
		{
			labelPtr label;
			printf("case direct\n");
			label = (labelPtr)malloc(sizeof(label));
			get_label(dstName, 0, 0, &label);
			printf("label_name:%s, label_value:%d, label_type:%d, label_link:%d\n", label->labelName, label->labelValue, label->labelType, label->labelLink);
			if(label->labelLink == EXTERN_LABEL)
			{
				dstInfo.ARE = E;
				dstInfo.data = 0;
				add_extern(label->labelName, IC);
				printf("ARE:%d\n", dstInfo.ARE);
			}
			else
			{
				dstInfo.ARE = R;
				dstInfo.data = label->labelValue;
			}
			printf("finish case direct\n");
		}
		wPtr.dataWordPtr = &dstInfo;
		printf("call to write code image with:data=%d, ARE=%d\n", wPtr.dataWordPtr->data, wPtr.dataWordPtr->ARE);
		write_code_image(wPtr, DATA_WORD);
		IC++;
		printf("finish write_code_image\n");
	}
	else
		if (!(((srcType == DIRECT_REGISTER) || (srcType == INDIRECT_REGISTER)) && ((dstType == DIRECT_REGISTER) || (dstType == INDIRECT_REGISTER))))	
		{
			infoWordReg dstInfoReg;
			printf("case reg\n");
			dstInfoReg.dstReg = atoi(dstName);
			dstInfoReg.ARE = A;
			dstInfoReg.srcReg = 0;
			dstInfoReg.rest = 0;
			wPtr.regWordPtr = &dstInfoReg;
			printf("call to write code image with:srcType=%d,dstType=%d, ARE=%d, rest=%d\n", wPtr.regWordPtr->srcReg, wPtr.regWordPtr->dstReg, wPtr.regWordPtr->ARE, wPtr.regWordPtr->rest);
			write_code_image(wPtr, DATA_REG_WORD);
			IC++;
			printf("finish write code image\n");
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
		skip_spaces(&line);
		if (*line == '\n')
		{
			add_error(MISSING_DATA);
			return 0;
		}
		while((num = get_data(&line))!= EOF)
		{
			
			word.data = num;
			printf("call write_data_image with %d\n", num);
			write_data_image(word);
			printf("finish data_image\n");
		}
	}

	if(type == STRING)
	{
		printf("case STRING\n");
		skip_spaces(&line);
		if (*line == '\n')
		{
			add_error(MISSING_DATA);
			return 0;
		}
		line++;
		while(((c = *line) != '\n')&&(c != '"'))
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

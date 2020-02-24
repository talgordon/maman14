#include <stdio.h>
#define MAX_WORDS 4096
#define A 4
#define R 2
#define E 1
#define IMMEDIATE 1
#define DIRECT 2
#define INDIRECT_REGISTER 4
#define DIRECT_REGISTER 8

typedef struct cmdWrd
{
	unsigned short ARE : 3;
	unsigned short src : 4;
	unsigned short dst : 4;
	unsigned short opcode : 4;
}cmdWord

typedef struct infoWrd
{
	unsigned short ARE : 3;
	unsigned short data : 12;
}infoWrd

typedef struct infoWord
{
	unsigned short ARE : 3;
	unsigned short srcReg : 3;
	unsigned short dstReg : 3;
	unsigned short rest : 6;
}infoWrdReg
typedef struct wrd 
{
	unsigned char src : 4;
	unsigned char dst : 4;
}addMethod

word buffer[MAX_WORDS];
addMethod addTable[16];
addTable[0] = {15, 7};
addTable[1] = {15, 15}; 
addTable[2] = {15, 7}; 
addTable[3] = {15, 7}; 
addTable[4] = {4, 7}; 
addTable[5] = {0, 7}; 
addTable[6] = {0, 7}; 
addTable[7] = {0, 7}; 
addTable[8] = {0, 7}; 
addTable[9] = {0, 6}; 
addTable[10] = {0, 6}; 
addTable[11] = {0, 7}; 
addTable[12] = {0, 15}; 
addTable[13] = {0, 6}; 
addTable[14] = {0, 0}; 
addTable[15] = {0, 0};  
 
char* opTable[16];
opTable[0] = "mov";
opTable[1] = "cmp";
opTable[2] = "add";
opTable[3] = "sub";
opTable[4] = "lea";
opTable[5] = "clr";
opTable[6] = "not";
opTable[7] = "inc";
opTable[8] = "dec";
opTable[9] = "jmp";
opTable[10] = "bne";
opTable[11] = "red";
opTable[12] = "prn";
opTable[13] = "jsr";
opTable[14] = "rts";
opTable[15] = "stop";

int translateFirst()
{
	cmdWord firstWord;
	/**get the opcode - first 4 bits in the word**/
	char *word;
	int opcode;
	word = getWord();
	if ((opcode = check_opTable(word)) < 0)
		/**error**/
	else
		firstWord.opcode = opcode;



	/**get the address method - next 8 bits in the word**/
	char * srcName;
	char * dstName;
	int srcType;
	int dstType;
	srcType = 0;
	dstType = 0;
	int numOfOp;/**how to check if legal number of operands?**/
	getOp(&srcName, &srcType, &dstName, &dstType, &numOfOp);
	if (!(srcType&addTable[firstWord.opcode].src) && (dstType&addTable[firstWord.opcode].dst))
		/**error**/
	else
	{
		firstWord.src = srcType;
		firstWord.dst = dstType;
	}
		

			
	/**get the ARE field - last 4 bits in the word**/
	firstWord.ARE = A;
	
	

	/**get the info words, one, two or non at all**/	
	if((srcType == IMMEDIATE) || (srcType == DIRECT))
	{
		infoWord srcInfo;
		if(srcType == IMMEDIATE)
		{
			srcInfo.data = two_complement(srcName);
			srcInfo.ARE = A;
		}
		else
		{
			srcInfo.data = to_binary(label_address(srcName));
			if(!is_extern(srcName))
				srcInfo.ARE = R;
			else
				srcInfo.ARE = E;
		}
	}
	else
	{
		if((srcType == INDIRECT_REGISTER) || (srcType == DIRECT_REGISTER))
		{
			infoWordReg srcInfoReg;
			srcInfoReg.srcReg = to_binary(srcName);
			srcInfoReg.ARE = A;
			if (dstType == INDIRECT_REGISTER) || (dstType == DIRECT_REGISTER))
				srcInfoReg.dstReg = to_binary(dstName);
			else
				srcInfoReg.dstReg = 0;
			srcInfoReg.rest = 0;
		}
	}

	if((dstType == IMMEDIATE) || (dstType == DIRECT))
	{
		infoWord dstInfo;
		if(dstType == IMMEDIATE)
		{
			dstInfo.data = two_complement(dstName);
			dstInfo.ARE = A;
		}
		else
		{
			dstInfo.data = to_binary(label_address(dstName));
			if(!is_extern(dstName))
				dstInfo.ARE = R;
			else
				dstInfo.ARE = E;
		}
	}
	else
	{
		if((dstType == INDIRECT_REGISTER) || (dstType == DIRECT_REGISTER))
		{
			infoWordReg dstInfoReg;
			dstInfoReg.dstReg = to_binary(dstName);
			dstInfoReg.ARE = A;
			dstInfoReg.srcReg = 0;
			dstInfoReg.rest = 0;
		}
	}
			
	
}

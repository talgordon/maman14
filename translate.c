#include <stdio.h>
#define MAX_WORDS 4096
typedef struct wrd
{
	unsigned short ARE : 3;
	unsigned short src : 4;
	unsigned short dst : 4;
	unsigned short opcode : 4;
}word

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
	word firstWord;
	/**get the opcode - first 4 bits in the word**/
	char *word;
	int opcode;
	word = getWord();
	if ((opcode = check_opTable(fword)) < 0)
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
	getOp(&srcName, &srcType, &dstName, %dstType, &numOfOp);
	if (!(srcType == addTable[firstWord.opcode].src) && (dstType = addTable[firstWord.opcode].dst))
		/**error**/
	else
	{
		firstWord.src = srcType;
		firstWord.dst = dstType;
	}
		

			
	/**get the ARE field - last 4 bits in the word**/
	if (!dstType & 4)/**is not a direct address**/
		firstWord.ARE = 4;
}

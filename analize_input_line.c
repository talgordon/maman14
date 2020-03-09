/*#include "labelsTable.h"*/

#include "data_structure.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define SANITY(x,y) \
{\
	if (!x)\
	{\
		printf(y);\
		return false;\
	}\
}
	
uint64_t DC = 0;
uint64_t IC = 0;
uint16_t L = 0;

addressMethod addressTable[16];
addressTable[0].src = 15;
addressTable[0].dst = 7;
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
addressTable[15].dst = 0; 

char buf[1000];
void get_line()
{
	int line=0;
	FILE *ptr;
	if((ptr = fopen("ps.as", "r")) == NULL)
	{
		error_check("COULDN'T OPEN FILE");
		exit(1);
	}

	fscanf(ptr, "%[^\n]", buf);
	fclose(ptr);
}

/**skip white spaces.
parameter: cmdLine - a pointer to a pointer to the input line, which is promote as long as the character in the line is a white space**/
void skip_spaces(char *line)
{
	while((*line == ' ')||(*line == '\t'))
		(*line)++;
}

/**check if the end of the line is legal - doesn't contain any characters which are not a white space
parameter: cmdLine - a pointer to a pointer to the input line, to scan the end of the line.
return: ERROR if the end of the line is ilegal, SUCCESS otherwise**/
int legal_EOL(char * line)
{
	while(*line != '\n') /**while it isn't the last character in the**/
	{
		if((*line == ' ')||(*line == '\t'))/**if it is a white space, move 								to the next character**/
			(*line)++;
		else /**if the character isn't a white space, error**/
		{
			printf("Extraneous text after end of commamd\n");
			error_check("LINE INVALID");
			/*flag?*/
		}
	}
	return SUCCESS;
	/**return SUCCESS; leagl end of line**/
}

int comma_logic(char *line)
{
	skip_spaces(line);
	if (*line != ',') /**check_comma**/
	{
		printf("Missing comma\n");
		error_check("LINE INVALID");
		/**(flag)**/
	}
	else /**found a comma**/
	{
		(*line)++;
		skip_spaces(line);
		if (*line == ',') /**check for multiple commas**/
		{
			printf("Multiple consecutive commas\n");
			error_check("LINE INVALID");
			/**(flag)**/
		}
	}
	return SUCCESS;	
}


uint64_t get_data(char **line)
{
	char *pch; /**pointer which help to read a number every time (before a space 				or a comma) and promote cmdLine**/
	char *num; /**pointer which contains the string representation of each number 				in the list.**/
	int i, numLength, sign;
	sign = 1;
	numLength = 0;
	num = (char *)malloc(10*sizeof(char));/**allocate place in the memory for 							num**/
	while(**line != '\n')/**while the input line isn't finished, scan the list**/
	{	
		skip_spaces(line);
		if(**line == '-') /**if there is a hyphen (maybe a minus sign) in the 						list of numbers**/
		{
			sign = -1;
			(*line)++; /**move to the next character in the input**/
		}
		else /**the user didnt insert a hyphen**/
		{
			memset(num, '\0', strlen(num)); /**initialize the num 							pointer, to aviod junk cells**/
			pch = strpbrk(*line," \t\n,"); /**find the first character in 					the input line which is a white space or a comma**/
			strncpy(num, *line, (pch - *line)); /**insert the string 					which comes before the character in pch to num**/
			*line = pch; /**promote cmdLine to after the string**/
			numLength = strlen(num);/**save the length of the number 							which was found**/
			/**scan all the string to check if it is a legal 				number**/			
			for(i=0;i<numLength;i++,num++)
			{
				if(!isdigit(*num)) /**if the current character is not 								a digit, error*/
				{
					printf("Invalid data - not an integer\n");
					/**return ERROR; flag, error handle**/
				}	
			}
			
		}
		skip_spaces(line);
		if (**line != ',') /**there is not a comma between two numbers, 					error**/
		{
			printf("Missing comma\n");
			/**return ERROR;**/
		}
		(*line)++; /**move to the next character**/
		skip_spaces(line);
		if (**line == ',') /**multiple commas, error**/
		{
			printf("Multiple consecutive commas\n");
			/**return ERROR;**/
		}
	}
	return atoi(num)*sign;
}


typedef enum types{LABEL , DATA , STRING , EXTERN , ENTRY, OTHER}types;
types get_word(char * line)
{
	/*char * cut_line = line;*/
	if(!(has_label(line)))/*check if is label*/
	{
		return LABEL;
	}
	/*cut_line = (skip_spaces(line));*/
	skip_spaces(line);

	if (line[0]=='.')/*check if is data/string/extern/entry*/
	{
		if(strcmp(line,".data")==0)
		{
			return DATA;
		}

		else if(strcmp(line,".string")==0)
		{
			return STRING;
		}

		else if(strcmp(line,".extern")==0)
		{
			return EXTERN;
		}

		else if(strcmp(line,".entry")==0)
		{
			return ENTRY;
		}
	}

	else
	{
		return OTHER;
	}
}

int has_label(char * line)
{
	while (!(isspace(*line)))
	{
		if (*line == ':')
		{
			if(*(line++) == ' ')
				return 0;	
		}
		line++;
	}
	return 1;
}


char* get_operand(char * line, int * srcType, int *dstType, char * srcName, char * dstName)
{
	char * pch;
	char * str;
	skip_spaces(line);
	switch(*line)
	{
		case '#':
		{
			*srcType=1;
			pch=(strpbrk(line," \t\n,"));
			strncpy(srcName,line,(pch-line));
			line=pch;
		}

		case '*':
		{
		    	*srcType=4;
			pch=(strpbrk(line," \t\n,"));
			strncpy(str,line,(pch-line));
			line=pch;
			strcpy(srcName, (str+1));    
		}
 		
		default :
		{
			*srcType=4;
			pch=(strpbrk(line," \t\n,"));
			strncpy(str,line,(pch-line));
			line=pch;
			if((*str == 'r')&&(*(str+1)< 8)&&(*(str+1) > 0)&&(strlen(str) == 2))
			{
				*srcType = 8;
				strcpy(srcName, (str+1));
			}
			else
			{
				if (find_label(str) == SUCCESS)
				{
					*srcType = 2;
					strcpy(srcName, str);
				}
				else
				{
					return error_check("LINE INVALID");
				}
			}
		}
	}

	line++;
	if(!(comma_logic(line)))
		error_check("LINE INVALID");
	line++;
	if((isspace(*line)))
		return SUCCESS;

	switch(*line)
	{
		case '#':
		{
			*dstType=1;
			pch=(strpbrk(line," \t\n,"));
			strncpy(dstName,line,(pch-line));
			line=pch;
		}

		case '*':
		{
		    	*dstType=4;
			pch=(strpbrk(line," \t\n,"));
			strncpy(str,line,(pch-line));
			line=pch;
			strcpy(dstName, (str+1));    
		}
 		
		default :
		{
			*dstType=4;
			pch=(strpbrk(line," \t\n,"));
			strncpy(str,line,(pch-line));
			line=pch;
			if((*str == 'r')&&(*(str+1)< 8)&&(*(str+1) > 0)&&(strlen(str) == 2))
			{
				*dstType = 8;
				strcpy(dstName, (str+1));
			}
			else
			{
				if (find_label(str) == SUCCESS)
				{
					*dstType = 2;
					strcpy(dstName, str);
				}
				else
				{
					error_check("LINE INVALID");
				}
			}
		}
	}

	if((legal_EOL(line))!=SUCCESS)	
		error_check("LINE INVALID");

	return SUCCESS;
}


char * save_label(char * line)
{
	uint16_t i = 0, start = 0, end = 0;
	this_char = line[i];
	while(this_char == ' ' || this_char == "\t")
	{
		i++;
		this_char = line[i];
	}
	start = i;
	
	SANITY(this_char > 'A' && this_char < 'Z' ||
	       this_char > 'a' && this_char < 'z'  , 
	       "message");
	while (this_char != ':')
	{
		i++;
		this_char = line[i];
	}
	end = i;
	SANITY(end-start < 32, "to long label name");
	
	char * labal_name = (char *) malloc(end - start);
	int8_t labal_type = -1;
	
	i++;
	this_char = line[i];
	while(this_char == ' ' || this_char == "\t")
	{
		i++;
		this_char = line[i];
	}
	
	if (this_char[i] == ".")
	{
		uint16_t b = 0;
		for (b = 0; b < sizeof(e_types)/sizeof(e_types[0]); b++)
		{
			if ( memcmp(line[i], e_types[b], sizeof(e_types[b])) == 0)
			{
				label_type = b;
				break;
			}
		}
		SANITY(label_type != -1, "unknown e_type");
	}
	
	memcpy(label_name, line[start], end-start);

	label * new_label = (label *)malloc(sizeof(label));
	new_label->labelName = label_name;
	new_label->labelType = label_type;
	new_label->labelValue = IC;
	labels_table.addLable(new_lable);
}
/*bool has_label(int16_t word)
{
	char this_word = word;
	while (this_word != -1)
	{
		if (this_word == ':')
		{
			return true;
		}
		i ++;
		this_char = line[i];
	}
	return false;
}*/

/*char * has_opcode(char * line)
{
	uint16_t i = 0;
	uint16_t j = 0;
	char this_char = line[i];
	while (this_char != -1)
	{
		for(j=0; i<16; j++)
		{
			if(strcmp(this_char, opcodeTable[j]));
			return opcodeTable[i];
		}
		i++;
		this_char = line[i];	
	}
	return false;
}*/
	/*char* cut_line = line;
	cut_line = skip_spaces(cut_line);
	uint16_t word_size = 0;
	while (*cut_line != " " || *cut_line != ",")
	{
		word_size++;
		cut_line++;	
	}
	char* word = (char*)malloc(word_size + 1);
	
	for (int i = 0; i < word_size; i++)
	{
		word[i] = line[i];
	}
	word[word_size] = "\0";	
	
	return word;*/



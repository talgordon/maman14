#include "analize_input_line.h"
#include "error.h"
#include "label.h"

/*A function that initializes global variables using code*/
void init()
{
	int i;
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
	
	inputLine = (char *)malloc(sizeof(char)*MAX_LINE);

	line_num = 0;
	IC = 100;
	DC = 0;
	L = 0;
}

/*A function that skip white spaces.*/
void skip_spaces(char **line)
{
	while((**line == ' ')||(**line == '\t'))
		(*line)++;
}

/*A function that check if the end of the line is legal - doesn't contain any characters which are not a white space*/
void legal_EOL(char ** line)
{
	while(**line != '\n') /*while it isn't the last character in the*/
	{
		if((**line == ' ')||(**line == '\t'))/*if it is a white space, move to the next character*/
			(*line)++;
		else /*if the character isn't a white space, error*/
		{
			add_error(TOO_MANY_OPERANDS);
		}
	}
}

/*A function that checks for a comma or not and advances the line accordingly*/
void comma_logic(char **line)
{
	skip_spaces(line);
	if (**line != ',') /*check_comma*/
	{
		add_error(MISSING_COMMA);
	}
	else /*found a comma*/
	{
		(*line)++;
		skip_spaces(line);
		if (**line == ',') /**check for multiple commas**/
		{
			add_error(MULTIPLE_COMMA);
		}
	}
}

/*A function that breaks down an input line and returns the following data every time*/
int get_data(char **line)
{
	char *pch; /*pointer which help to read a number every time (before a space or a comma) and promote cmdLine*/
	char *num; /*pointer which contains the string representation of each number in the list.*/
	int i, numLength, sign;
	sign = 1;
	numLength = 0;
	num = (char *)malloc(10*sizeof(char));/**allocate place in the memory for num**/
	skip_spaces(line);

	if(**line != '\n')/*while the input line isn't finished, scan the list*/
	{	
		
		if(**line == '-') /*if there is a hyphen (maybe a minus sign) in the list of numbers*/
		{
			sign = -1;
			(*line)++; /*move to the next character in the input*/
		}
		memset(num, '\0', strlen(num)); /*initialize the num pointer, to aviod junk cells*/
		pch = strpbrk(*line," \t\n,"); /*find the first character in the input line which is a white space or a comma*/
		strncpy(num, *line, (pch - *line)); /*insert the string which comes before the character in pch to num*/
		*line = pch; /*promote cmdLine to after the string*/
		numLength = strlen(num);/*save the length of the number which was found*/
		/*scan all the string to check if it is a legal number*/
				
		for(i=0;i<numLength;i++)
		{
			if(!isdigit(num[i])) /*if the current character is not a digit, error*/
			{
				add_error(INVALID_DATA);
			}	
		}
		skip_spaces(line);
		if ((**line != ',')&&(**line != '\n')) /*there is not a comma between two number, error*/
		{
			add_error(MISSING_COMMA);
		}
		if (**line != '\n')
			(*line)++; /*move to the next character*/
		skip_spaces(line);
		if (**line == ',') /*multiple commas, error*/
		{
			add_error(MULTIPLE_COMMA);
		}

		return (atoi(num)*sign);
	}
	else
		return EOF;
}

/*A function that check if the line is label and return 0/1*/
int is_label(char * line)
{
	while (!(isspace(*line)))/*Skipping all the profits*/
	{
		if (*line == ':')/*If is label*/
		{
			if(isspace(*(++line)))
				return 0;	
		}
		line++;
	}
	return 1;/*if is not a label*/
}

/*A function that analize an input line. Reads a first word from the line to the space and returns an enum according to the type it has inserted*/
types get_word(char * line[40], char ** word)
{
	
	char * pch;
	memset(*word, '\0', strlen(*word));
	skip_spaces(line);
	if ((**line) == '\n')/*Check if is end of the line-return END*/
	{
		return END;	
	}
	if((is_label(*line)) == 0)/*Check if is label-return LABEL*/
	{
		pch=(strpbrk(*line," \t\n,"));
		strncpy(*word,*line,(pch-*line));
		*line=pch;
		return LABEL;
	}
	pch=(strpbrk(*line," \t\n,"));
	strncpy(*word,*line,(pch-*line));
	*line=pch;
	skip_spaces(line);
	if (**word == '.')/*check if is data/string/extern/entry*/
	{
		if(strcmp(*word,".data")==0)/*Check if is data-return DATA*/
		{
			return DATA;
		}

		else if(strcmp(*word,".string")==0)/*Check if is string-return STRING*/
		{
			return STRING;

		}

		else if(strcmp(*word,".extern")==0)/*Check if is extrn-return EXTERN*/
		{
			return EXTERN;
		}

		else if(strcmp(*word,".entry")==0)
		{
			return ENTRY;
		}
	}
	return CODE;/*If is not label/data/string/extern/entry-it is opcode-return CODE*/
}

/*A function that analize a line from the input, reads the operands in the insruction*/
void get_operand(char * line, int *srcType, int *dstType, char ** srcName, char ** dstName, int loop)
{
	labelPtr label;
	char * pch;
	char * str;
	str = (char *)malloc(sizeof(char)*MAX_WORD);
	memset(str, '\0', strlen(str));
	label=(labelPtr)malloc(sizeof(label));
	skip_spaces(&line);	
	if (*line == '\n')/*If the beginning of the line is empty, no operands*/
	{
		*srcType = 0;
		*srcName = NULL;
		*dstType = 0;
		*dstName = NULL;
		return;
	}
	pch=(strpbrk(line," \t\n,"));
	strncpy(str,line,(pch-line));
	line=pch;
	skip_spaces(&line);
	if (*line == '\n')
	{
		*srcType = 0;
		*srcName = NULL;
	}
	else/*If its have a operands*/
	{
		comma_logic(&line);/*Checks if its have a comma*/
		skip_spaces(&line);
		switch(*str)/*Switch that checks the first operand type and copy the type to dstName*/
		{
			case '#':/*If is direct address-initializes the srcType accordingly*/
			{
				*srcType=1;
				strcpy(*srcName, (str+1));
				break;
			}

			case '*':/*If is indirect address-initializes the srcType accordingly*/
			{	

			    	*srcType=4;
				strcpy(*srcName, (str+2));
				break;
			}
	 		
			default :
			{
				*srcType=4;
				if(*str == 'r')/*If is direct register address-initializes the srcType accordingly*/
				{
					str++;
					if ((atoi(str) < 8) && (atoi(str) > 0))
					{
						if(*(str+1) == '\0')
						{
							*srcType = 8;
							strcpy(*srcName, str);
						}
					}
				}
				else/*If is not one of the previous cases*/
				{
					if (loop == 2)
						get_label(str, 0, 0, &label);
					if((label!=NULL)||(loop == 1))/*Is label*/
					{
						*srcType = 2;
						strcpy(*srcName, str);
					}
					else/*If is not of the previous cases,error*/
					{
						add_error(INVALID_SRC_TYPE);
					}
				}
				break;
			}
		}
		memset(str, '\0', strlen(str));
		pch=(strpbrk(line," \t\n,"));
		strncpy(str,line,(pch-line));
		line=pch;
	}
	
	switch(*str)/*A same switch that checks the secand operand type and copy the type to dstName*/
	{
		case '#':
		{
			*dstType=1;
			strcpy(*dstName, (str+1));		
			break;
		}
		case '*':
		{
		    	*dstType=4;
			strcpy(*dstName, (str+2));  
			break;  
		}
 		
		default :
		{

			*dstType=4;
			if(*str == 'r')
			{
				str++;
				if ((atoi(str) < 8) && (atoi(str) > 0))
				{
					if(*(str+1) == '\0')
					{
						*dstType = 8;
						strcpy(*dstName, str);
					}
				}
			}
			else
			{
				if (loop == 2)				
					get_label(str, 0, 0, &label);	

				if((label!=NULL)||(loop == 1))
				{
					*dstType = 2;
					strcpy(*dstName, str);
				}
				else
				{
					add_error(INVALID_DST_TYPE);
				}
			}
			break;
			
		}
	}
	legal_EOL(&line);
}




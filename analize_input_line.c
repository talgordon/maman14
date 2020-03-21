#include "analize_input_line.h"
#include "error.h"
#include "label.h"

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

	for(i = 0; i<1000; i++)	
	{
		buf[i] = (char *)malloc(sizeof(char)*40);
		strcpy(buf[i], "empty line");	
	}

	line_num = 0;
	IC = 100;
	DC = 0;
	L = 0;
}

/*A function that reads a line from the input file.*/
void get_line(int argc, char * argv[])
{
	FILE *ptr;
	int i, index;
	for (i=1; i<argc; i++)/*Loop that run until the file was read*/
	{	
		if((ptr = fopen(argv[i], "r")) == NULL)/*Check if the file is empty-print error and exit*/
		{
			error_check("CANNOT_OPEN_FILE");
			exit(1);
		}
		index = 0;
		memset(buf[index], '\0', strlen(buf[index]));
		while(fgets(buf[index], sizeof(buf), ptr)!=NULL)/*Income the line in the file into an array called buf and magnification the index*/
		{
			fputs(buf[index],stdout);
			fputs("",stdout);
			index++;
		}
		fclose(ptr);/*Close the file*/
	}
}

/**skip white spaces.
parameter: cmdLine - a pointer to a pointer to the input line, which is promote as long as the character in the line is a white space**/
void skip_spaces(char **line)
{
	while((**line == ' ')||(**line == '\t'))
		(*line)++;
}

/**check if the end of the line is legal - doesn't contain any characters which are not a white space
parameter: cmdLine - a pointer to a pointer to the input line, to scan the end of the line.
return: ERROR if the end of the line is ilegal, SUCCESS otherwise**/
void legal_EOL(char ** line)
{
	while(**line != '\n') /**while it isn't the last character in the**/
	{
		if((**line == ' ')||(**line == '\t'))/**if it is a white space, move to the next character**/
			(*line)++;
		else /**if the character isn't a white space, error**/
		{
			error_check("LINE_INVALID");
		}
	}
}

/*A function that checks for a comma or not and advances the line accordingly*/
void comma_logic(char **line)
{
	skip_spaces(line);
	if (**line != ',') /*check_comma*/
	{
		error_check("LINE_INVALID");
	}
	else /*found a comma*/
	{
		(*line)++;
		skip_spaces(line);
		if (**line == ',') /**check for multiple commas**/
		{
			error_check("LINE_INVALID");
		}
	}
}


int get_data(char **line)
{
	char *pch; /**pointer which help to read a number every time (before a space or a comma) and promote cmdLine**/
	char *num; /**pointer which contains the string representation of each number in the list.**/
	int i, numLength, sign;
	sign = 1;
	numLength = 0;
	num = (char *)malloc(10*sizeof(char));/**allocate place in the memory for num**/
	skip_spaces(line);
	printf("in get_data, line is:%c, end of line?:%d\n", **line, (**line == '\n'));	
	if(**line != '\n')/**while the input line isn't finished, scan the list**/
	{	
		
		if(**line == '-') /**if there is a hyphen (maybe a minus sign) in the list of numbers**/
		{
			sign = -1;
			(*line)++; /**move to the next character in the input**/
			printf("is a negative number\n");
		}
		memset(num, '\0', strlen(num)); /**initialize the num pointer, to aviod junk cells**/
		pch = strpbrk(*line," \t\n,"); /**find the first character in the input line which is a white space or a comma**/
		strncpy(num, *line, (pch - *line)); /**insert the string which comes before the character in pch to num**/
		*line = pch; /**promote cmdLine to after the string**/
		numLength = strlen(num);/**save the length of the number which was found**/
		/**scan all the string to check if it is a legal number**/
		printf("num is:%s, length:%d\n", num, numLength);			
		for(i=0;i<numLength;i++)
		{
			if(!isdigit(num[i])) /**if the current character is not a digit, error*/
			{
				error_check("INVALID_DATA");
			}	
		}
		skip_spaces(line);
		if ((**line != ',')&&(**line != '\n')) /**there is not a comma between two number, error**/
		{
			error_check("INVALID_DATA");
		}
		if (**line != '\n')
			(*line)++; /**move to the next character**/
		skip_spaces(line);
		if (**line == ',') /**multiple commas, error**/
		{
			error_check("INVALID_DATA");
		}
		printf("finish one ran,atoi(num):%d, sign:%d, going to return :%d\n", atoi(num), sign, atoi(num)*sign);
		return (atoi(num)*sign);
	}
	else
		printf("is in else\n");
		return EOF;
}


int is_label(char * line)/*A function that check if the line is label and return 0/1*/
{
	printf("in is label\n");
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
	char * str=NULL;
	memset(*word, '\0', strlen(*word));
	printf("in get word, line:%s\n", *line);
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
		printf("there is . in the word\n");
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

/*A function that analize a aline from the input, reads the operands in the */
void get_operand(char * line, int *srcType, int *dstType, char ** srcName, char ** dstName, int loop)
{
	labelPtr label;
	char * pch;
	char * str;
	str = (char *)malloc(sizeof(char)*MAX_WORD);
	label=(labelPtr)malloc(sizeof(label));
	skip_spaces(&line);	
	if (*line == '\n')
	{
		printf("no operands\n");
		*srcType = 0;
		*srcName = NULL;
		*dstType = 0;
		*dstName = NULL;
		return;
	}
	pch=(strpbrk(line," \t\n,"));
	strncpy(str,line,(pch-line));
	line=pch;
	printf("str:%s\n", str);
	comma_logic(&line);
	skip_spaces(&line);
	printf("*line:%c\n", *line);
	if (*line == '\n')
	{
		printf("one operand\n");
		*srcType = 0;
		*srcName = NULL;
	}
	else
	{
		printf("in get operands, line:%s\n", line);
		switch(*str)
		{
			case '#':
			{
				printf("case #\n");
				*srcType=1;
				strcpy(*srcName, (str+1));
				printf("srcName:%s\n", *srcName);
				break;
			}

			case '*':
			{	
				printf("case *\n");
			    	*srcType=4;
				strcpy(*srcName, (str+2));
				printf("srcName:%s\n", *srcName);
				break;
			}
	 		
			default :
			{
				printf("case default\n");
				*srcType=4;
				printf("*str:%c\n", *str);
				if(*str == 'r')
				{
					str++;
					printf("atoi(str):%d\n", atoi(str));
					if ((atoi(str) < 8) && (atoi(str) > 0))
					{
						if(*(str+1) == '\0')
						{
							printf("case r\n");
							*srcType = 8;
							strcpy(*srcName, str);
							printf("srcName:%s\n", *srcName);
						}
					}
				}
				else
				{
					if (loop == 2)
						get_label(str, 0, 0, &label);
					if((label!=NULL)||(loop == 1))
					{
						printf("case label\n");
						*srcType = 2;
						strcpy(*srcName, str);
						printf("srcName:%s\n", *srcName);
					}
					else
					{
						error_check("LINE_INVALID");
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
	
	printf("*str before check dst:%c\n", *str);
	switch(*str)
	{
		case '#':
		{
			printf("case #\n");
			*dstType=1;
			strcpy(*dstName, (str+1));		
			break;
		}
		case '*':
		{
			printf("case *\n");
		    	*dstType=4;
			strcpy(*dstName, (str+2));  
			break;  
		}
 		
		default :
		{

			printf("case default\n");
			*dstType=4;
			printf("*str:%c\n", *str);
			if(*str == 'r')
			{
				str++;
				printf("atoi(str):%d\n", atoi(str));
				if ((atoi(str) < 8) && (atoi(str) > 0))
				{
					if(*(str+1) == '\0')
					{
						printf("case r\n");
						*dstType = 8;
						strcpy(*dstName, str);
						printf("dstName:%s\n", *dstName);
					}
				}
			}
			else
			{
				printf("before get_label\n");
				if (loop == 2)				
					get_label(str, 0, 0, &label);	
				printf("after get label\n");
				if((label!=NULL)||(loop == 1))
				{
					printf("is label\n");
					*dstType = 2;
					strcpy(*dstName, str);
					printf("?\n");
				}
				else
				{
					error_check("LINE_INVALID");
				}
			}
			break;
			
		}
	}
	legal_EOL(&line);
}




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


void get_line(int argc, char * argv[])
{
	FILE *ptr;
	int i, index;
	for (i=1; i<argc; i++)
	{	
		if((ptr = fopen(argv[i], "r")) == NULL)
		{
			error_check("CANNOT_OPEN_FILE");
			exit(1);
		}
		index = 0;
		memset(buf[index], '\0', strlen(buf[index]));
		
		while(fgets(buf[index], sizeof(buf), ptr)!=NULL)
		{
			fputs(buf[index],stdout);
			fputs("",stdout);
			index++;
		}
		fclose(ptr);
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

void comma_logic(char **line)
{
	skip_spaces(line);
	if (**line != ',') /**check_comma**/
	{
		error_check("LINE_INVALID");
	}
	else /**found a comma**/
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
	while(**line != '\n')/**while the input line isn't finished, scan the list**/
	{	
		skip_spaces(line);
		if(**line == '-') /**if there is a hyphen (maybe a minus sign) in the list of numbers**/
		{
			sign = -1;
			(*line)++; /**move to the next character in the input**/
		}
		else /**the user didnt insert a hyphen**/
		{
			memset(num, '\0', strlen(num)); /**initialize the num pointer, to aviod junk cells**/
			pch = strpbrk(*line," \t\n,"); /**find the first character in the input line which is a white space or a comma**/
			strncpy(num, *line, (pch - *line)); /**insert the string which comes before the character in pch to num**/
			*line = pch; /**promote cmdLine to after the string**/
			numLength = strlen(num);/**save the length of the number which was found**/
			/**scan all the string to check if it is a legal number**/			
			for(i=0;i<numLength;i++,num++)
			{
				if(!isdigit(*num)) /**if the current character is not a digit, error*/
				{
					error_check("INVALID_DATA");
				}	
			}
			
		}
		skip_spaces(line);
		if (**line != ',') /**there is not a comma between two number, error**/
		{
			error_check("INVALID_DATA");
		}
		(*line)++; /**move to the next character**/
		skip_spaces(line);
		if (**line == ',') /**multiple commas, error**/
		{
			error_check("INVALID_DATA");
		}
	}
	return atoi(num)*sign;
}


int is_label(char * line)
{
	printf("in is label\n");
	while (!(isspace(*line)))
	{
		if (*line == ':')
		{
			if(isspace(*(++line)))
				return 0;	
		}
		line++;
	}
	return 1;
}

types get_word(char * line[40], char ** word)
{
	
	char * pch;
	char * str=NULL;
	memset(*word, '\0', strlen(*word));
	printf("in get word, line:%s\n", *line);
	skip_spaces(line);
	if ((**line) == '\n')
	{
		return END;	
	}
	if((is_label(*line)) == 0)/*check if is label*/
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
		if(strcmp(*word,".data")==0)
		{
			return DATA;
		}

		else if(strcmp(*word,".string")==0)
		{
			return STRING;

		}

		else if(strcmp(*word,".extern")==0)
		{
			return EXTERN;
		}

		else if(strcmp(*word,".entry")==0)
		{
			return ENTRY;
		}
	}
	return CODE;
}

void get_operand(char * line, int *srcType, int *dstType, char ** srcName, char ** dstName)
{
	labelPtr label;
	char * pch;
	char * str;
	str = (char *)malloc(sizeof(char)*MAX_WORD);
	label=(labelPtr)malloc(sizeof(label));
	skip_spaces(&line);
	printf("in get operands, line:%s\n", line);
	switch(*line)
	{
		case '#':
		{
			printf("case #\n");
			*srcType=1;
			pch=(strpbrk(line," \t\n,"));
			strncpy(*srcName,line,(pch-line));
			line=pch;
			printf("srcName:%s\n", *srcName);
		}

		case '*':
		{	
			printf("case *\n");
		    	*srcType=4;
			pch=(strpbrk(line," \t\n,"));
			strncpy(str,line,(pch-line));
			line=pch;
			strcpy(*srcName, (str+1));
			printf("srcName:%s\n", *srcName);
		}
 		
		default :
		{
			printf("case default\n");
			*srcType=4;
			memset(str, '\0', strlen(str));
			pch=(strpbrk(line," \t\n,"));
			strncpy(str,line,(pch-line));
			line=pch;
			printf("*str:%c\n", *str);
			if(*str == 'r')
			{
				str++;
				printf("atoi(str):%d\n", atoi(str));
				if ((atoi(str) < 8) && (atoi(str) > 0))
				{
					if(*(++str) == '\0')
					{
						printf("case r\n");
						*srcType = 8;
						strcpy(*srcName, (str+1));
						printf("srcName:%s\n", *srcName);
					}
				}
			}
			else
			{
				get_label(str, 0, 0, &label);
				if(label!=NULL)
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
		}
	}

	comma_logic(&line);
	skip_spaces(&line);

	switch(*line)
	{
		case '#':
		{
			*dstType=1;
			pch=(strpbrk(line," \t\n,"));
			strncpy(*dstName,line,(pch-line));
			line=pch;
		}
		case '*':
		{
		    *dstType=4;
			pch=(strpbrk(line," \t\n,"));
			strncpy(str,line,(pch-line));
			line=pch;
			strcpy(*dstName, (str+1));    
		}
 		
		default :
		{
			*dstType=4;
			pch=(strpbrk(line," \t\n,"));
			strncpy(str,line,(pch-line));
			line=pch;
			if(*str == 'r')
			{
				if ((atoi(++str) < 8) && (atoi(str) > 0))
				{
					if(*(++str) == '\0')
					{
						*dstType = 8;
						strcpy(*dstName, (str+1));
						printf("!");
					}
				}
			}
			else
			{
				get_label(str, 0, 0, &label);
				if(label!=NULL)
				{
					*dstType = 2;
					strcpy(*dstName, str);
					printf("?\n");
				}
				else
				{
					error_check("LINE_INVALID");
				}
			}
			
		}
	}
	legal_EOL(&line);
}




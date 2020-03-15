#include "analize_input_line.h"
#include "analize_code_word.h"
#include "error.h"

void init()
{
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
}

char * buf[1000];
void get_line(int argc, char * argv[])
{
	FILE *ptr;
	int i;
	for (i=0; i<argc; i++)
	{	
		if((ptr = fopen(argv[i], "r")) == NULL)
		{
			error_check("CANNOT_OPEN_FILE");
			exit(1);
		}
		line_num = 0;
		while(!feof(ptr))
		{
			fscanf(ptr, "%s", buf);	
			line_num++;
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

types get_word(char ** line, char ** word)
{
	char * pch;
	char * str=NULL;
	skip_spaces(line);
	if (**line == "\n")
	{
		return END;	
	}
	if(!(has_label(*line)))/*check if is label*/
	{
		pch=(strpbrk(*line," \t\n,"));
		strncpy(*word,*line,(pch-*line));
		*line=pch;
		return LABEL;
	}

	skip_spaces(&line);

	if (line[0]=='.')/*check if is data/string/extern/entry*/
	{
		if(strcmp(line,".data")==0)
		{
			pch=(strpbrk(*line," \t\n,"));
			strncpy(*word,*line,(pch-*line));
			*line=pch;
			return DATA;
		}

		else if(strcmp(line,".string")==0)
		{
			pch=(strpbrk(*line," \t\n,"));
			strncpy(*word,*line,(pch-*line));
			*line=pch;
			return STRING;
		}

		else if(strcmp(line,".extern")==0)
		{
			pch=(strpbrk(*line," \t\n,"));
			strncpy(*word,*line,(pch-*line));
			*line=pch;
			return EXTERN;
		}

		else if(strcmp(line,".entry")==0)
		{
			pch=(strpbrk(*line," \t\n,"));
			strncpy(*word,*line,(pch-*line));
			*line=pch;
			return ENTRY;
		}
	}
	pch=(strpbrk(*line," \t\n,"));
	strncpy(*word,*line,(pch-*line));
	*line=pch;
	return OTHER;
}

void get_operand(char * line, int *srcType, int *dstType, char ** srcName, char ** dstName)
{
	labelPtr label;
	label=(labelPtr)malloc(sizeof(label));
	char * pch;
	char * str=NULL;
	skip_spaces(&line);
	switch(*line)
	{
		case '#':
		{
			*srcType=1;
			pch=(strpbrk(line," \t\n,"));
			strncpy(*srcName,line,(pch-line));
			line=pch;
		}

		case '*':
		{
		    *srcType=4;
			pch=(strpbrk(line," \t\n,"));
			strncpy(str,line,(pch-line));
			line=pch;
			strcpy(*srcName, (str+1));    
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
				strcpy(*srcName, (str+1));
			}
			else
			{
				get_label(str, 0, 0, &label);
				if(label!=NULL)
				{
					*srcType = 2;
					strcpy(*srcName, str);
				}
				else
				{
					error_check("LINE INVALID");
				}
			}
		}
	}

	comma_logic(&line);
	line++;
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
			if((*str == 'r')&&(*(str+1)< 8)&&(*(str+1) > 0)&&(strlen(str) == 2))
			{
				*dstType = 8;
				strcpy(*dstName, (str+1));
			}
			else
			{
				get_label(str, 0, 0, &label);
				if(label!=NULL)
				{
					*dstType = 2;
					strcpy(*dstName, str);
				}
				else
				{
					error_check("LINE INVALID");
				}
			}
		}
	}

	legal_EOL(&line);

}


int main(int argc, char * argv[])
{
	char * line;
	int * srcType=1;
	int * dstType=2;
	char * srcName=srcName;
	char * dstName=dstName;
	bufIndex = 0;

	get_line(argc, argv);
	get_word(buf);
	get_operand(line, srcType,dstType,srcName,dstName);
	return 0;
}

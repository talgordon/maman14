#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*#include "error.c"*/

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

void skip_spaces(char *line)
{
	while((*line == ' ')||(*line == '\t'))
		(*line)++;
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

int legal_EOL(char * line)
{
	while(*line != '\n') 
	{
		if((*line == ' ')||(*line == '\t'))
			(*line)++;
		else
		{
			printf("Extraneous text after end of commamd\n");
			error_check("LINE INVALID");
			/*flag?*/
		}
	}
	return SUCCESS;
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



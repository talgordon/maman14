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
int legal_EOL(char ** line)
{
	while(**line != '\n') /**while it isn't the last character in the**/
	{
		if((**line == ' ')||(**line == '\t'))/**if it is a white space, move to the next character**/
			(*line)++;
		else /**if the character isn't a white space, error**/
		{
			printf("Extraneous text after end of commamd\n");
			/**return ERROR, flag?, error handle?**/
		}
	}
	/**return SUCCESS; leagl end of line**/
}

int comma_logic(char **line)
{
	skip_spaces(line);
	if (**line != ',') /**check_comma**/
	{
		printf("Missing comma\n");
		/**return error (flag), error handle**/
	}
	else /**found a comma**/
	{
		line++;
		skip_spaces(line);
		if (**line == ',') /**check for multiple commas**/
			printf("Multiple consecutive commas\n");
			/**return error (flag), error handle**/
	}
	/**succuss**/	
}

uint64_t get_data(char **line)
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
					printf("Invalid data - not an integer\n");
					/**return ERROR; flag, error handle**/
				}	
			}
			
		}
		skip_spaces(line);
		if (**line != ',') /**there is not a comma between two numbers, error**/
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
bool line_first_analyzer(char * line)
{
	char * cut_line = line;
	if has_label(line)
	{
		cut_line = save_label(line);
		SANITY (cut_line != NULL , "Error when try.....");
	}
	cut_line = ignore_spaces(cut_line);
	if (cut_line[0] == '.')
	{
		//implement
	}
	cut_line....ignore
	
	if (has_opcode(line))
	{
		//implement
	}

}

bool has_label(char * line)
{
	uint16_t i = 0;
	char this_char = line[i];
	while (this_char != -1)
	{
		if (this_char == ':')
		{
			return true;
		}
		i ++;
		this_char = line[i];
	}
	return false;
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




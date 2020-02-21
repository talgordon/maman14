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

char * ignore_spaces(char * line)
{
	int i = 0;
	while(this_char == ' ' || this_char == "\t")
	{
		i++;
		this_char = line[i];
	}
}


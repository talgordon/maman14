#include "analize_input_line.h"
#include "label.h"
#include "error.h"
#include "analize_code_word.h"
#include "modules.h"

/*A function that handles a guidance that has data*/
void data_handle(char * labelName, int type)
{
	if (get_flag("LABEL") == IS_TRUE)/*If have label*/
	{
		add_label(labelName, DC, DATA_LABEL, NOT_LINKED_LABEL);/*Add the label to the linked list*/
		set_flag("LABEL", IS_FALSE);
	}
	translate_data(type, inputLine);/*Call to translate_data to encode to binary*/
}

/*A function that handles a guidance that has entry*/
void entry_handle()/*second loop*/
{
	char *word;
	word = (char *)malloc(sizeof(char)*MAX_WORD);
	while (get_word(&inputLine, &word)!= END)	
	{
		update_label(ENTRY_LABEL, LABEL_LINK, NOTHING, NOTHING, word);/*Updating a label in the linked list*/
	}
	free(word);
}

/*A function that handles a guidance that has extern*/
void extern_handle()
{
	char *word;
	word = (char *)malloc(sizeof(char)*MAX_WORD);
	while (get_word(&inputLine, &word)!= END)
	{
		add_label(word, NO_ADDRESS, UNDEFINED_LABEL, EXTERN_LABEL);/*Add the label to the linked list*/
	}
	free(word);
}

/*A function that handles insruction*/
void code_handle_first(char * labelName, char * word)
{
	int srcType, dstType, opcode;
	char * srcName;
	char * dstName;
	wordPtr wPtr;
	srcName = (char *)malloc(sizeof(char)*MAX_WORD);
	dstName = (char *)malloc(sizeof(char)*MAX_WORD);
	if (get_flag("LABEL") == IS_TRUE)/*If have label*/
	{
		add_label(labelName, IC, CODE_LABEL, NOT_LINKED_LABEL);/*Add the label to the linked list*/
		set_flag("LABEL", IS_FALSE);
	}
	if ((opcode = find_opcode(word)) == ERROR)/*If the opcode is illegal, error*/
		add_error(UNEXISTED_OPCODE);

	get_operand(inputLine, &srcType, &dstType, &srcName, &dstName, FIRST);/*Call to get_operand*/
	L = 1;
	if (dstType != NO_OPERAND)
	{
		L++;
		if (!((srcType == DIRECT_REGISTER || srcType == INDIRECT_REGISTER) && (dstType == DIRECT_REGISTER || dstType == INDIRECT_REGISTER)) && (srcType != NO_OPERAND))
			L++;
	}
	translate_code(wPtr, opcode, srcType, dstType);
	IC = IC + L;
	free(srcName);
	free(dstName);
	
}

/*A function that call to finish_translate to finish a translate the input line*/
void code_handle_second()
{
	wordPtr wPtr;
	IC++;
	finish_translate(inputLine, wPtr);
}
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
	addressTable[5].src = NO_OPERAND;
	addressTable[5].dst = 7; 
	addressTable[6].src = NO_OPERAND;
	addressTable[6].dst = 7; 
	addressTable[7].src = NO_OPERAND;
	addressTable[7].dst = 7; 
	addressTable[8].src = NO_OPERAND;
	addressTable[8].dst = 7; 
	addressTable[9].src = NO_OPERAND;
	addressTable[9].dst = 6; 
	addressTable[10].src = NO_OPERAND;
	addressTable[10].dst = 6;    
	addressTable[11].src = NO_OPERAND;
	addressTable[11].dst = 7;  
	addressTable[12].src = NO_OPERAND;
	addressTable[12].dst = 15; 
	addressTable[13].src = NO_OPERAND;
	addressTable[13].dst = 6;  
	addressTable[14].src = NO_OPERAND;
	addressTable[14].dst = NO_OPERAND;
	addressTable[15].src = NO_OPERAND;
	addressTable[15].dst = NO_OPERAND;
	
	inputLine = (char *)malloc(sizeof(char)*MAX_LINE);

	line_num = 0;
	IC = 100;
	DC = 0;
	L = 0;
}

void free_list(char * name)
{
	if(strcmp(name, "error") == 0)
	{
		errorPtr tmp;
		while (error_head != NULL)
		{
			tmp = error_head;
			error_head = error_head->next;
			free(tmp);
		}
	}
	else
	{	
		memWordPtr tmp;
		if(strcmp(name, "memWord") == 0)
		{
			while (data_head != NULL)
			{
				tmp = data_head;
				data_head = data_head->next;
				free(tmp);
			}
		}
		else
		{
			labelPtr tmp;
			if(strcmp(name, "label") == 0)
			{
				while (label_head != NULL)
				{
					tmp = label_head;
					label_head = label_head->next;
					free(tmp->labelName);
					free(tmp);
				}
			}
			else
			{	
				externPtr tmp;
				if(strcmp(name, "extern") == 0)
				{
					while (extern_head != NULL)
					{
						tmp = extern_head;
						extern_head = extern_head->next;
						free(tmp->externName);
						free(tmp);
					}
				}		
			}
		}
	}
}


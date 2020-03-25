#include "analize_input_line.h"
#include "label.h"
#include "error.h"
#include "analize_code_word.h"
#include "modules.h"

/*A function that handles a guidance that has data*/
void data_handle(char * labelName, int type)
{
	if (get_flag("LABEL") == 1)/*If have label*/
	{
		add_label(labelName, DC, DATA_LABEL, NOT_LINKED_LABEL);/*Add the label to the linked list*/
		set_flag("LABEL", 0);
	}
	translate_data(type, inputLine);/*Call to translate_data to encode to binary*/
}

/*A function that handles a guidance that has entry*/
void entry_handle()/*second loop*/
{
	char * word;
	word = (char *)malloc(sizeof(char)*MAX_WORD);
	while (get_word(&inputLine, &word)!= END)
		update_label(ENTRY_LABEL, LABEL_LINK, 0, 0, word);/*Updating a label in the linked list*/
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
	if (get_flag("LABEL") == 1)/*If have label*/
	{
		add_label(labelName, IC, CODE_LABEL, NOT_LINKED_LABEL);/*Add the label to the linked list*/
		set_flag("LABEL", 0);
	}
	if ((opcode = find_opcode(word)) < 0)/*If the opcode is illegal, error*/
		add_error(UNEXISTED_OPCODE);

	get_operand(inputLine, &srcType, &dstType, &srcName, &dstName, 1);/*Call to get_operand*/
	L = 1;
	if (dstType != 0)
	{
		L++;
		if (!((srcType == DIRECT_REGISTER || srcType == INDIRECT_REGISTER) && (dstType == DIRECT_REGISTER || dstType == INDIRECT_REGISTER)) && (srcType != 0))
			L++;
	}
	
	translate_code(wPtr, opcode, srcType, dstType);
	IC = IC + L;
	
}

/*A function that call to finish_translate to finish a translate the input line*/
void code_handle_second()
{
	wordPtr wPtr;
	IC++;
	finish_translate(inputLine, wPtr);
}

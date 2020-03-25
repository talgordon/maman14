
#include "analize_input_line.h"
#include "label.h"
#include "error.h"
#include "analize_code_word.h"
#include "modules.h"

void data_handle(char * labelName, int type)
{
	printf("in data_handle\n");
	if (get_flag("LABEL") == 1)
	{
		add_label(labelName, DC, DATA_LABEL, NOT_LINKED_LABEL);
		set_flag("LABEL", 0);
		printf("in data_handle, label %s was added\n", labelName);
	}
	printf("in data_handle, call translate data with %s\n", inputLine);
	translate_data(type, inputLine);
	printf("finish translate_data\n");
	
}

void entry_handle()/*second loop*/
{
	char *word;
	word = (char *)malloc(sizeof(char)*MAX_WORD);
	printf("in entry handle, buf is:%s\n", inputLine);
	while (get_word(&inputLine, &word)!= END)
		update_label(ENTRY_LABEL, LABEL_LINK, 0, 0, word);
}

void extern_handle()
{
	char *word;
	word = (char *)malloc(sizeof(char)*MAX_WORD);
	printf("in extern handle, buf is:%s\n", inputLine);
	while (get_word(&inputLine, &word)!= END)
	{
		printf("label to add:%s\n", word);
		add_label(word, NO_ADDRESS, UNDEFINED_LABEL, EXTERN_LABEL);
		printf("label %s was added\n", word);
	}
}

void code_handle_first(char * labelName, char * word)
{
	int srcType, dstType, opcode;
	char * srcName;
	char * dstName;
	wordPtr wPtr;
	srcName = (char *)malloc(sizeof(char)*MAX_WORD);
	dstName = (char *)malloc(sizeof(char)*MAX_WORD);
	printf("in code handle, buf is:%s\n", inputLine);
	if (get_flag("LABEL") == 1)
	{
		add_label(labelName, IC, CODE_LABEL, NOT_LINKED_LABEL);
		set_flag("LABEL", 0);
		printf("label %s was added\n", labelName);
	}
	if ((opcode = find_opcode(word)) < 0)
		add_error(UNEXISTED_OPCODE);
	printf("line for get_operands:%s\n", inputLine);
	get_operand(inputLine, &srcType, &dstType, &srcName, &dstName, 1);
	L = 1;
	if (dstType != 0)/*change to handle a case when two operands are represnted in 1 info word*/
	{
		L++;
		if (!((srcType == DIRECT_REGISTER || srcType == INDIRECT_REGISTER) && (dstType == DIRECT_REGISTER || dstType == INDIRECT_REGISTER)) && (srcType != 0))
			L++;
	}
	printf("opcode:%d, srcType:%d, dstType:%d, srcName:%s, dstName:%s, L:%d\n", opcode, srcType, dstType, srcName, dstName, L);
	translate_code(wPtr, opcode, srcType, dstType);
	IC = IC + L;
	
}
void code_handle_second()
{
	wordPtr wPtr;
	printf("in second code handle, buf:%s\n", inputLine);
	IC++;
	finish_translate(inputLine, wPtr);
	printf("finish finish translate\n");
	printf("IC:%d\n", IC);	
}

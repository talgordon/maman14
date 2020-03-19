
#include "analize_input_line.h"
#include "label.h"
#include "error.h"
#include "analize_code_word.h"
#include "modules.h"

void data_handle(char * labelName, int type)
{
	if (get_flag("LABEL") == 1)
	{
		add_label(labelName, DC, DATA_LABEL);
		set_flag("LABEL", 0);
	}

	translate_data(type, buf[line_num]);
	
}

void entry_handle()/*second loop*/
{
	char *word;
	while (get_word(&buf[line_num], &word)!= END)
		add_label(word, LABEL_TYPE, ENTRY_LABEL);
}

void extern_handle()
{
	char *word;
	while (get_word(&buf[line_num], &word)!= END)
		add_label(word, NO_ADDRESS, EXTERN_LABEL);
}

void code_handle_first(char * labelName, char * word)
{
	int srcType, dstType, opcode;
	char * srcName;
	char * dstName;
	wordPtr wPtr;
	printf("in code handle, buf[line_num] is:%s\n", buf[line_num]);
	if (get_flag("LABEL") == 1)
	{
		add_label(labelName, IC, CODE_LABEL);
		set_flag("LABEL", 0);
		printf("label %s was added\n", labelName);
	}
	if ((opcode = find_opcode(word)) < 0)
		error_check("OPCODE");
	printf("line for get_operands:%s\n", buf[line_num]);
	get_operand(buf[line_num], &srcType, &dstType, &srcName, &dstName);
	L = 1;
	if (srcType != 0)/*change to handle a case when two operands are represnted in 1 info word*/
		L++;
	if (dstType != 0)
		L++;
	printf("opcode:%d, srcType:%d, dstType:%d, srcName:%s, dstName:%s, L:%d\n", opcode, srcType, dstType, srcName, dstName, L);
	translate_code(wPtr, opcode, srcType, dstType);
	IC = IC + L;
	
}
void code_handle_second()
{
	wordPtr wPtr;
	finish_translate(buf[line_num], wPtr);
	IC = IC + L;
}

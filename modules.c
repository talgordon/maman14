#include "translate.h"
#include "analize_input_line.h"
void data_handle();
void extern_handle();
void entry_handle();
void code_handle();
void label_handle(char ** labelName);
/**
int main()
{
	char * word;
	char * labelName;
	if (get_word(&word) == LABEL)
		labelName = word;
		get_word()
	else
		if (DATA || STRING)
		data_handle(labelName, type);
}**/
void data_handle(char * labelName, int type)
{
	if (get_flag("LABEL") == 1)
	{
		add_label(labelName, DC, DATA_LABEL);
		set_flag("LABEL", 0);
	}

	translate_data(type, buf[line_num]);
	
}

void entry_handle()
{
	char *word;
	while (get_word(&word, &buf[line_num])!= END)
		update_lable(ENTRY_LABEL, LABEL_TYPE, word);
}

void extern_handle()
{
	char *word;
	while (get_word(&word, &buf[line_num])!= END)
		add_lable(word, NO_ADDRESS, EXTERN_LABEL);
}

void code_handle_first(char * labelName, char * word)
{
	int srcType, dstType, opcode;
	char * srcName;
	char * dstName;
	wordPtr wPtr;
	if (get_flag("LABEL") == 1)
	{
		add_label(labelName, IC, CODE_LABEL);
		set_flag("LABEL", 0);
	}
	if ((opcode = find_opcode(word)) < 0)
		error_check("OPCODE");
	get_operand(buf[line_num], &srcType, &dstType, &srcName, &dstName);
	L = 1;
	if (srcType != 0)
		L++;
	if (dstType != 0)
		L++;
	translate_code(wPtr, opcode, srcType, dstType, srcName, dstName);
	IC = IC + L;
	
}
void code_handle_second()
{
	wordPtr wPtr;
	finish_translate(buf[line_num], wPtr);
	IC = IC + L;
}

#include "analize_input_line.h"
#include "analize_code_word.h"
#include "error.h"
#include "label.h"
#include "modules.h"
#include "build.h"

/*Main program*/
int main(int argc, char * argv[])
{
	char * word;
	char * buf;
	char * labelName;
	FILE *ptr;
	int i;
	int wordType;
	word = (char *)malloc(sizeof(char)*MAX_WORD);
	labelName = (char *)malloc(sizeof(char)*MAX_WORD);
	buf = (char *)malloc(sizeof(char)*MAX_LINE);
	init();/*Initialization of the variabels*/
	for (i=1; i<argc; i++)/*Run on the file*/
	{	
		if((ptr = fopen(argv[i], "r")) == NULL)/*If could not open the file, error*/
		{
			add_error(CANNOT_OPEN_FILE);
			exit(1);
		}
		line_num = 0;/*new file*/
		memset(buf, '\0', strlen(buf));
		
		while(fgets(buf, MAX_LINE, ptr)!=NULL)/*scan all the lines in the file*/
		{
			inputLine = buf;
			set_flag("LABEL",IS_FALSE);
			
			if (!((inputLine[0] == '\n')||((inputLine[0] == '/')&&(inputLine[1] == '*')&&(inputLine[strlen(inputLine)-3] == '*')&& (inputLine[strlen(inputLine)-2] == '/'))))/*Check if the word is symbol*/
			{	
				wordType = get_word(&inputLine, &word);
				if (wordType == LABEL)/*If the word is label*/
				{
					set_flag("LABEL", IS_TRUE);/*Turns on the flag- there is an label*/
					strcpy(labelName, word);
					wordType = get_word(&inputLine, &word);
				}
				switch (wordType)/*Check the type*/
				{
					case DATA:/*If is data or string-call to data_handle to treatment*/
					case STRING:
					{
						data_handle(labelName, wordType);
						break;
					}
					case ENTRY:/*If is entry-does not do anything. Willl be addressed in the second pass*/
					{
						break;
					}
					case EXTERN:/*If is entry-call to extern_handle to treatment*/
					{
						extern_handle();
						break;
					}
					case CODE:/*This is instruction-call to code_handle_first to treatment*/
					{
						code_handle_first(labelName, word);
						break;
					}
					case END:
					{
						break;	
					}
				
				}
			}
		
			line_num++;
			memset(buf, '\0', strlen(buf));

		}
		fclose(ptr);/*Close the file*/
	}	
	if (get_flag("ERROR") == IS_TRUE)/*there are errors in the code*/
	{
		print_error();/*Print all the error*/
		return 0;/*finish the program. There is no reason to keep going since the code is illigal*/
		
	}
	update_label(IC, LABEL_VALUE, DATA, LABEL_TYPE, "ALL");/*Updates the values in the symbol tabel*/
	
	IC = 100;
	for (i=1; i<argc; i++)/*Run on the file*/
	{	
		if((ptr = fopen(argv[i], "r")) == NULL)/*If could not to open the file,error*/
		{
			add_error(CANNOT_OPEN_FILE);
			exit(1);
		}
		line_num = 0;/**new file**/
		memset(buf, '\0', MAX_LINE);
		
		while(fgets(buf, MAX_LINE, ptr)!=NULL)/*scan all the lines in the file*/
		{
			inputLine = buf;
			
			if (!((inputLine[0] == '\n')||((inputLine[0] == '/')&&(inputLine[1] == '*')&&(inputLine[strlen(inputLine)-3] == '*')&& (inputLine[strlen(inputLine)-2] == '/'))))
			{			
				wordType = get_word(&inputLine, &labelName);
				if (wordType == LABEL)/*If the word is label*/
				{
					wordType = get_word(&inputLine, &word);
				}
				switch (wordType)/*Swith that check the type*/
				{
					case DATA:/*If is data/string/extern-skip*/
					case STRING:
					case EXTERN:
					{
						break;
					}
					case ENTRY:/*If is entry-call to entry_handle to treatment*/
					{
						entry_handle();
						break;
					}
					case CODE:/*If is entry-call to entry_handle to treatment*/
					{
						code_handle_second();
						break;
					}
					case END:
					{
						break;	
					}
				
				}
			}
			line_num++;
			memset(buf, '\0', MAX_LINE);
		}
		fclose(ptr);/*Close the file*/
	}

	if (get_flag("ERROR") == IS_TRUE)/*there are errors in the code*/
	{
		print_error();/*Print the error*/
		return 0;
	
	}
	else
		build_output();/*Call to build_out to build the file output*/
	/*Call to free and free_list to free all*/
	free(buf);
	free(labelName);
	free(word);
	free_list("error");
	free_list("memWord");
	free_list("label");
	free_list("extern");
	return 0;	


	
}

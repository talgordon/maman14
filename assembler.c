#include "analize_input_line.h"
#include "error.h"
#include "label.h"
#include "modules.h"
#include "build.h"
int main(int argc, char * argv[])
{
	char * word;
	char * labelName;
	FILE *ptr;
	int i, line_num;
	int wordType;
	word = (char *)malloc(sizeof(char)*MAX_WORD);
	labelName = (char *)malloc(sizeof(char)*MAX_WORD);
	init();/**add IC, DC, L.. and other values**/
	printf("finish init\n");
	for (i=1; i<argc; i++)
	{	
		if((ptr = fopen(argv[i], "r")) == NULL)
		{
			error_check("CANNOT_OPEN_FILE");
			exit(1);
		}
		printf("file opened successfuly\n");
		line_num = 0;/**new file**/
		memset(buf[line_num], '\0', strlen(buf[line_num]));
		
		while(fgets(buf[line_num], sizeof(buf), ptr)!=NULL)/*scan all the lines in the file*/
		{
			printf("line was read\n");
			wordType = get_word(&buf[line_num], &labelName);
			if (wordType == LABEL)
			{
				printf("word is a label\n");
				set_flag("LABEL", 1);
				wordType = get_word(&buf[line_num], &word);
			}
			switch (wordType)
			{
				case DATA:
				case STRING:
				{
					printf("word is data or string\n");
					data_handle(labelName, wordType);
					break;
				}
				case ENTRY:
				{
					printf("word is entry\n");
					break;
				}
				case EXTERN:
				{
					printf("word is extern\n");
					extern_handle();
					break;
				}
				case CODE:
				{
					printf("word is code\n");
					printf("rest line:%s\n", buf[line_num]);
					code_handle_first(labelName, word);
					break;
				}
				case END:
				{
					break;	
				}
			
			}
			printf("moving to the next line, line_num:%d\n", line_num);
			line_num++;
		}
		fclose(ptr);
	}	
	if (get_flag("ERROR") == 1)/*there are errors in the code*/
	{
		print_error();
		return 0;
	}
	update_label(IC, LABEL_VALUE, DATA, "ALL");
	

	line_num = 0;
	IC = 100;
	for (i=1; i<argc; i++)
	{	
		if((ptr = fopen(argv[i], "r")) == NULL)
		{
			error_check("CANNOT_OPEN_FILE");
			exit(1);
		}
		line_num = 0;/**new file**/
		memset(buf[line_num], '\0', strlen(buf[line_num]));
		
		while(fgets(buf[line_num], sizeof(buf), ptr)!=NULL)/*scan all the lines in the file*/
		{
			wordType = get_word(&buf[line_num], &labelName);
			if (wordType == LABEL)
			{
				wordType = get_word(&buf[line_num], &word);
			}
			switch (wordType)
			{
				case DATA:
				case STRING:
				case EXTERN:
				{
					break;
				}
				case ENTRY:
				{
					entry_handle();
					break;
				}
				case CODE:
				{
					code_handle_second();
					break;
				}
				case END:
				{
					break;	
				}
			
			}
			line_num++;
		}
		fclose(ptr);
	}
	build_output();
	return 0;	


	
}

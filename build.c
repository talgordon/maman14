
#include "analize_code_word.h"
#include "build.h"
#include "label.h"
#include "analize_input_line.h"
void build_output()
{
	build_object();
	build_entry();
	build_extern();
}
void build_entry()
{
	labelPtr label;
	FILE *fp;
	label = (labelPtr)malloc(sizeof(label));
	label = label_head;
	fp = fopen("ps.ent", "w");
	while(label!=NULL)
	{
		if(label->labelType == ENTRY_LABEL)
			fprintf(fp,"%s\t%d\n", label->labelName, label->labelValue);
		label = label->next;
	}
	fclose(fp);
}

void build_extern()
{
	labelPtr label;
	FILE *fp;
	int mask, i;
	mask = 1;
	label = (labelPtr)malloc(sizeof(label));
	label = label_head;
	fp = fopen("ps.ext", "w");
	for(i = 0; i < IC; i++)
	{
		if(buffer[i]&mask)
		{
			while(label!=NULL)
			{
				if((label->labelType == EXTERN_LABEL)&&(label->labelValue == buffer[i]>>2))
					fprintf(fp,"%s\t%d\n", label->labelName, i);
				label = label->next;
			}
		}
	}
	fclose(fp);
}
void build_object()
{	
	FILE *fp;
	fp = fopen("ps.ob", "w");
	fprintf(fp,"\n\t%d,\t%d\n", IC, DC);
	print_mem();
	fclose(fp);
}


#include "analize_code_word.c"
void build_entry();
void build_extern();
void build_object();
void build_output();
int main()
{
	add_label("MAIN", 100, ENTRY_LABEL);
	add_label("fn1", 104, EXTERN_LABEL);
	add_label("L3", 114, EXTERN_LABEL);
	add_label("LIST", 137, ENTRY_LABEL);
	build_entry();
	build_extern();
	build_object();
	return 0;
	
}
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
	fprintf("\n\t%d,\t%d\n", IC, DC);
	print_mem();
	fclose(fp);
}

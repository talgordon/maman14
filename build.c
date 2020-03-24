#include "analize_code_word.h"
#include "build.h"
#include "label.h"
#include "analize_input_line.h"

/*A function that creates the program output files by calling to build_object, build_entry and build_extern*/
void build_output()
{
	build_object();
	build_entry();
	build_extern();
}

/*A function that creates the program output entry files*/
void build_entry()
{
	labelPtr label;
	FILE *fp;
	label = (labelPtr)malloc(sizeof(label));
	label = label_head;
	fp = fopen("ps.ent", "w");/*Open the file ps.ent*/
	while(label!=NULL)/*Run as long as label equal to NULL and print the label name and his value.*/
	{
		if(label->labelLink == ENTRY_LABEL)/*Check if is entry-print*/
			fprintf(fp,"%s\t%d \n", label->labelName, label->labelValue);
		label = label->next;/*If not a entry-one step ahead*/
	}
	fclose(fp);/*Close the file*/
}

/*A function that creates the program output extern files*/
void build_extern()
{
	FILE *fp;
	fp = fopen("ps.ext", "w");/*Open the file ps.ext*/
	print_extern(fp);
	fclose(fp);/*Close the file*/
}

/*A function that creates the program output object files*/
void build_object()
{	
	FILE *fp;
	fp = fopen("ps.ob", "w");/*Open the file ps.ob*/
	fprintf(fp,"\n\t%d,\t%d\n", IC, DC);/*Print the IC and DC*/
	print_mem(fp);/*Call to the function print_mem that print ????*/
	fclose(fp);/*Close the file*/
}

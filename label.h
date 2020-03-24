#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NO_ADDRESS 0
#define MAX_LABEL 31
typedef struct label * labelPtr;
typedef struct label
{
	char * labelName;
	unsigned int labelValue;
	unsigned int labelType;
	unsigned int labelLink;
	labelPtr next;
}label;

typedef struct externLabel * externPtr;
typedef struct externLabel
{
	char * externName;
	unsigned int externValue;
	externPtr next;
}externLabel;

enum labeltypes{UNDEFINED_LABEL, DATA_LABEL, CODE_LABEL};
enum labelLinks{NOT_LINKED_LABEL, EXTERN_LABEL, ENTRY_LABEL};
enum labelFields{LABEL_NAME, LABEL_VALUE, LABEL_TYPE, LABEL_LINK};

labelPtr label_head;
externPtr extern_head;

int isreserved(char * word);
int isillegal(char * word);
void add_label(char * name, int value, int type, int link);
void get_label(char *name, int feature, int featureType, labelPtr* label);
int update_label(int update, int updateType, int labelID, int IDType, char *name);
void print_label();

void add_extern(char * name, int value);	
void print_extern(FILE * fp);


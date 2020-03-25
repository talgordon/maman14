#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NO_ADDRESS 0
#define MAX_LABEL 31
typedef struct label * labelPtr;

/*struct for label with the name, value, type and link*/
typedef struct label
{
	char * labelName;
	unsigned int labelValue;
	unsigned int labelType;
	unsigned int labelLink;
	labelPtr next;
}label;

typedef struct externLabel * externPtr;

/*struct for extern label with the name and value*/
typedef struct externLabel
{
	char * externName;
	unsigned int externValue;
	externPtr next;
}externLabel;

/*Enum with the type of label*/
enum labeltypes{UNDEFINED_LABEL, DATA_LABEL, CODE_LABEL};
/*Enum with the links of label*/
enum labelLinks{NOT_LINKED_LABEL, EXTERN_LABEL, ENTRY_LABEL};
/*Enum with the type of fields*/
enum labelFields{LABEL_NAME, LABEL_VALUE, LABEL_TYPE, LABEL_LINK};

labelPtr label_head;
externPtr extern_head;

/*A function that accepts a word and check if the word is word that the code knows*/
int isreserved(char * word);
/*A function that check if the word that she get is legal andd return 0/1*/
int isillegal(char * word);
/*A function that add the label to a linked list*/
void add_label(char * name, int value, int type, int link);
/*A function get a anew label*/
void get_label(char *name, int feature, int featureType, labelPtr* label);
/*A function that update a new label*/
int update_label(int update, int updateType, int labelID, int IDType, char *name);
/*A function that print a label name, label value and his type*/
void print_label();

/*A function that add a extern to a linked list with exrerns*/
void add_extern(char * name, int value);	
/*A function that print the linked list with externs*/
void print_extern(FILE * fp);


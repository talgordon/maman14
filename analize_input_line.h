#include "label.h"
#include <ctype.h>
	
unsigned int DC = 0;
unsigned int IC = 0;
unsigned int L = 0;

typedef enum type{LABEL , DATA , STRING , EXTERN , ENTRY, OTHER} types;

void get_line(int argc, char * argv[]);
void skip_spaces(char **line);
void legal_EOL(char ** line);
void comma_logic(char **line);
int get_data(char **line);
int has_label(char * line);
types get_word(char * line);
void get_operand(char * line, int * srcType, int *dstType, char * srcName, char * dstName);


#include <ctype.h>
#define MAX_WORD 80
#define MAX_LINE 127	
unsigned int DC;
unsigned int IC;
unsigned int L;
char * buf[1000];
typedef enum type{LABEL , DATA , STRING , EXTERN , ENTRY, CODE, END} types;

typedef struct addressMethod *addrMethodPtr;

typedef struct addressMethod{
	unsigned int src : 4;
	unsigned int dst : 4;
}addressMethod;

addressMethod addressTable[16];

void get_line(int argc, char * argv[]);
void skip_spaces(char **line);
void legal_EOL(char ** line);
void comma_logic(char **line);
void init();
int get_data(char **line);
int is_label(char * line);
types get_word(char * line[], char ** word);
void get_operand(char * line, int * srcType, int *dstType, char ** srcName, char ** dstName, int loop);


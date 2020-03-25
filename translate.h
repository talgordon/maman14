typedef struct memWord* memWordPtr;/*Type pointer memWord*/

/*Struct of memory word with int word and the index*/
typedef struct memWord{
	unsigned int word;
	unsigned int index;
	memWordPtr next;
}memWord;

/*Enum with the type is possible*/
enum types{CODE_WORD, DATA_WORD, DATA_REG_WORD};
int DC, IC, L;

memWordPtr dataHead;

/*An array in the size of the memory*/
unsigned int buffer[4096];

/*A function that adds a memory word to data image*/
int write_data_image(dataWord dWord);
/*A function that adds a memory word to code image*/
int write_code_image(wordPtr ptr, int type);
/*A functio that print a nenory word*/
int print_mem();


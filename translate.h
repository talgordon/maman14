
typedef struct memWord* memWordPtr;

typedef struct memWord{
	unsigned int word;
	unsigned int index;
	memWordPtr next;
}memWord;

enum types{CODE_WORD, DATA_WORD, DATA_REG_WORD};
int DC, IC, L;

memWordPtr dataHead;

unsigned int buffer[4096];

int write_data_image(dataWord dWord);
int write_code_image(wordPtr ptr, int type);
int print_mem();

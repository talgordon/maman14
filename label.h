#define NO_ADDRESS 0
typedef struct label * labelPtr;
typedef struct label
{
	char * labelName;
	unsigned int labelValue;
	unsigned int labelType;
	labelPtr next;
}label;


enum labeltypes{UNDEFINED_LABEL, DATA_LABEL, ENTRY_LABEL, EXTERN_LABEL, CODE_LABEL};
enum labelFields{LABEL_NAME, LABEL_VALUE, LABEL_TYPE};

labelPtr label_head;

void add_label(char * name, int value, int type);
void get_label(char *name, int feature, int featureType, labelPtr* label);
int update_label(int update, int updateType, int labelValue, char *name);
void print_label();


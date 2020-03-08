#include "data_structure.h"

PSW_hold PSW;
int get_flag(char * name)
{
	if (strcmp(name, "ERROR") == 0)
		return PSW.ERROR;
	if (strcmp(name, "LABEL") == 0)
		return PSW.LABEL;
	if (strcmp(name, "Z") == 0)
		return PSW.Z;
	return -1;
}

int set_flag(char *name, int value)
{
	if (strcmp(name, "ERROR") == 0)
		PSW.ERROR = value;
	else
	{
		if (strcmp(name, "LABEL") == 0)
			PSW.LABEL = value;
		else
		{   
			if (strcmp(name, "Z") == 0)
				PSW.Z = value;	
			else
				return -1;
		}
	}
	return 0;
}



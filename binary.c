#include <stdio.h>
#include <stdint.h>
#define BITS_IN_INT 64

/*A function that returns a number in method two complement*/
int two_complement(int num)
{
	return (~num)+1;
}



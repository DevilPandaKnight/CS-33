#include <stdio.h>

/* Declaration of data type where 4 bytes are packed
into an unsigned */
typedef unsigned packed_t;

//A. the original function are performing logic right shift to the word
//so it does not retain the sign bit after extract

//B.
/* Extract byte from word.  Return as signed integer */
int xbyte(packed_t word, int bytenum){
	int byte = word << ((3 - bytenum) << 3);
	return byte >> 24;
}

int main(int argc, char *argv[]) {
	printf("%x\n",xbyte(0xabcdef12, 3));
}
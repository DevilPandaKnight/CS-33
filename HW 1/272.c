#include <stdio.h>
#include <string.h>

//A. the original function subtract the unsigned from a signed int
//so the signed int will be convert to unsigned int and the result will be unsigned
//so the comparsion will always true

//B.
void copy_int(int val, void *buf, int maxbytes) {
	int size = sizeof(val);
	if (maxbytes - size >= 0) {
		memcpy(buf, &val, sizeof(val));
	}
}

int main(int argc, char *argv[]) {
	
}
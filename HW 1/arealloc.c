#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void * arealloc(void *ptr, size_t nmemb, size_t size){
	//if nmemb*size overflow, then set ENOMEM return NULL.
	size_t len = nmemb*size;
	if (len/nmemb != size) {
		errno = ENOMEM;
		return NULL;
	}
	return realloc(ptr, len);
}

int main(int argc, char *argv[]) {
	
}
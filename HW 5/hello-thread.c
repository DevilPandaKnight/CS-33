#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* thread(void *vargp);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		return 0;
	}
	int n = atoi(argv[1]);
	pthread_t tid_array[n];
	for (int i = 0;i<n;i++) {
		pthread_create(&tid_array[i], NULL, thread,NULL);
	}
	for (int i = 0;i<n;i++) {
		pthread_join(tid_array[i], NULL);
	}
	exit(0);
}

void* thread(void *vargp){
	printf("hello world\n");
	return NULL;
}
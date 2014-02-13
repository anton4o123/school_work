#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* hello(void* arg) {
	int *a = (int*)malloc(sizeof(int));
	*a=10;
	int* array = (int*)arg;
	int i;
	int sum=0;
	for(i=0;i<10000;++i) {
		sum+=array[i];
	}
	*a = sum / 10000;
	
	return a;
}

int main() {
	int array[10000];
	int i;
	for(i=0;i<10000;++i) {
		array[i]=i%255;
	}
	pthread_t thread;
	pthread_create(&thread, NULL, hello, (void*)array);

	void *result;
	pthread_join(thread, &result);
	printf("%d\n", *(int*)result);
	
	free(result);
	pthread_exit(NULL);

	return 0;
}

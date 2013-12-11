#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

void *print_hello(void *data) {
	size_t thread_num = (size_t)data;

	printf("Hello world from thread: %zd\n", thread_num);

	pthread_exit(NULL);
}

void main() {
	pthread_t threads[5];
	size_t i;
	
	for(i = 0; i < NUM_THREADS; i++) {
		pthread_create(&threads[i],NULL,print_hello,(void*)i);
	}
	
	pthread_exit(NULL);

}

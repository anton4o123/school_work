#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10000

int cmp(void* n1, void* n2) {
	return (*(int*)n1)-(*(int*)n2);
}

void* merge_sort(void* arr) {
	qsort((int*)arr, SIZE/2, sizeof(int), (void*)cmp);
	return (void*)0;
}

int main() {
	srand((unsigned)time(NULL));
	int arr[SIZE];
	int i;
	void *status;
	for(i=0; i<SIZE; ++i) {
		arr[i]=rand()/(RAND_MAX/(SIZE*10)+1);
	}
	
	pthread_t thread1;
	pthread_t thread2;
	pthread_create(&thread1, NULL, merge_sort, (void*)arr);
	pthread_join(thread1, &status);
	pthread_create(&thread2, NULL, merge_sort, (void*)&arr[SIZE/2]);
	pthread_join(thread2, &status);

	for(i=0; i<SIZE; ++i) {
		printf("%d\n",arr[i]);
	}
	pthread_exit(NULL);
	return 0;
}

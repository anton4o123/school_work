#include <pthread.h>
#include <stdio.h>


typedef struct sized_array {
	int *pArray;
	int size;
} sized_array;

void* sum(sized_array arg) {
	sized_array new_arg, new_arg2;

	if(arg.size==1) {
		return (int*)(arg.pArray[0]);
	}
	
	if(arg.size==2) {
		return (int*)(arg.pArray[0]+arg.pArray[1]);
	}
	new_arg.pArray=arg.pArray;
	new_arg.size=arg.size/2;
	new_arg2.pArray=arg.pArray+arg.size/2;
	new_arg2.size=arg.size/2;
	return ((int)sum(new_arg)+(int)sum(new_arg2));
}

void main() {
	sized_array arr;
	int a[8];
	arr.pArray=a;
	arr.size=8;
	int i;
	
	for(i=0; i<8; ++i) {
		a[i]=i+1;
		printf("%d\n", a[i]);
	}
	
	pthread_t thread1;
	void *result;
	pthread_create(&thread1, NULL, sum, &arr);
	//pthread_join(thread1, &result);
	//printf("%d\n", (int)result);
	
}

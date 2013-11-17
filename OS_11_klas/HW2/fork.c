#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	int p=123;
	printf("Hello World\n");
	pid_t pid=fork();
	if(pid==-1) {
		perror("fork");
		return 1;
	}
	else if(pid==0) {
		printf("Hello from child\n");
		p=200;
	}
	else {
		printf("Hello from parent\n");
	}
	
	printf("%d\n",p);
/*	printf("Hello World2\n");
	fork();
	printf("Hello World3\n");
	sleep(10000);*/
	return 0;
}

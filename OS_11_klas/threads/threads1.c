#include <stdio.h>
#include <pthread.h>

int hello(int arg) {
	printf("Hello (%d)\n", arg);
}

int func(char *arg, char** arg2) {
	return 0;
}

int main() {
	int (*p)(int) = hello;
	int (*q)(char*, char**) = func;

	p(1);

	return 0;
}

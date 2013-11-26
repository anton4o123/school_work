#include <stdio.h>

void step() {
	printf("|________|\n");
}

void doodler() {
	printf("_O_\n");
	printf(" O \n");	
}

void main() {
	system("clear");
	step();
	doodler();
	getchar();
}

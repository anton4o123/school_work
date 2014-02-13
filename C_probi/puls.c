#include <stdio.h>
#include <unistd.h>

void main() {
	double a;
	
	printf("Molq vavedete vashiq puls: ");scanf("%lg",&a);
	
	while(1) {
		printf("a");
		sleep(60/a);
	}
}

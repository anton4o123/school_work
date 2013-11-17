#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	printf("1\n");
	execl("/bin/ls","/bin/ls","-l",NULL);
	printf("2\n");


	return 0;
}

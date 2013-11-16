#include <stdio.h>
#include <unistd.h>

int main()
{
	char buf[10];

	read(0,buf,10);
	printf("%c",buf[0]);

	return 0;
}

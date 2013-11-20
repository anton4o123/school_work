#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char bor[200],*check;
	char **argo;

	strcpy(bor,"ls");
	argo[0]=bor;
	execvp(argo[0],argo);

	return 0;
}

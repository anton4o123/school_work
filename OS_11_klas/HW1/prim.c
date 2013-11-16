#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void function_for_writing(int f)
{
	int i=0;
	char bukva;

	while((i<10) && (read(f,&bukva,1)))
	{
		if(bukva=='\n')
			i++;
		printf("%c",bukva);
	}
}

int main(int argc,char* argv[])
{
int i=0,j,f;
char bukva;

	if(argc==1)
	{
		while((i<10) && (read(0,&bukva,1)))
		{
			printf("%c",bukva);
			if(bukva=='\n')
				i++;
		}
	}
	else
	{
		if(argc==2)
		{
			f=open(argv[1],O_RDONLY,0);
			if(f==-1)
			{
				fprintf(stderr, "head: cannot open '%s' for reading : No such file or directory\n",argv[j]);
				return 0;
			}
			function_for_writing(f);
			close(f);
		}
		else
		{
			j=1;
			while(j<argc)
			{
				if(*argv[j]!='-')
				{
					f=open(argv[j],O_RDONLY,0);
					if(f==-1)
					{
						fprintf(stderr, "head: cannot open '%s' for reading : No such file or directory\n",argv[j]);
						return 0;
					}
					printf("==> %s <==\n",argv[j]);
					function_for_writing(f);
					close(f);
					j++;
				}
				else
				{
					while((i<10) && (read(0,&bukva,1)))
					{
						printf("%c",bukva);
						if(bukva=='\n')
							i++;
					}
					j++;
				}
				i=0;
			}
		}
	}
	return 0;
}

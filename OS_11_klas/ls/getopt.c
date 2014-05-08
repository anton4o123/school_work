#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int aflag=0, bflag=0, c;
	
	while((c=getopt(argc, argv, "ab?:"))!=-1) {
		switch(c) {
			case 'a':aflag=1;break;
			case 'b':bflag=1;break;
			case '?': return 1;
			default: abort();
		}
	}
	
	printf("aflag: %d, bflag: %d\n", aflag, bflag);
	
	return 0;
}

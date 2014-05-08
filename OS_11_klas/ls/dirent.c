#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char* argv[]) {
	struct dirent *dir;
	DIR* pDir;
	
	if(argc!=2) {
		printf("Wrong number of arguments!\n");
		exit(1);
	}
	
	pDir=opendir(argv[1]);
	
	if(pDir==NULL) {
		printf("Cannot open dir!\n");
		exit(2);
	}
	
	while((dir=readdir(pDir))!=NULL) {
		printf("%s\n", dir->d_name);
	}
	
	closedir(pDir);
	
	return 0;
}

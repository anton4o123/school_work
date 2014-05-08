#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
	struct stat sb;
	
	if(argc!=2) {
		printf("Wrong number of arguments!\n");
		return 1;
	}
	
	if(stat(argv[1], &sb)==-1) {
		perror("stat");
		return 2;
	}
	
	switch(sb.st_mode & S_IFMT) {
		case S_IFBLK: printf("Block device!\n");break;
		case S_IFDIR: printf("Directory!\n");break;
		case S_IFREG: printf("Regular file!\n");break;
	}
	
	printf("Owner %ld group %ld\n", (long)sb.st_uid, (long)sb.st_gid);
	
	printf("Last access time: %ld\n", sb.st_atime);

	printf("Last access time: %s\n", (char*)ctime(&sb.st_mtime));
	
	return 0;
}

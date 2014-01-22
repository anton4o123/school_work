#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int writer(int f) {
	char* buf=malloc(100*sizeof(char));
	int p,err;
	
	do {
		p=read(f,buf,100);
		if(p==-1) {
			perror("cat:");
			return -2;
		}
		err=write(STDOUT_FILENO,buf,p);
		if(err==-1) {
			perror("cat:");
			return -3;
		}
	} while(p);
	free(buf);
}

int main(int argc, char* argv[]) {
	int f,i,err;
	
	if(argc>1) {
		for(i=0;i<argc;i++) {
			f=open(argv[i],O_RDONLY,0);
			if(f==-1) {
				perror("cat:");
				return -1;
			}
			err=writer(f);
			if(err<0) {
				perror("cat:");
				return err;
			}
			err=close(f);
			if(err==-1) {
				perror("cat:");
				return -4;
			}
		}
	} else {
		err=writer(STDIN_FILENO);
		if(err<0) {
			perror("cat:");
			return err;
		}
	}
	return 0;
}

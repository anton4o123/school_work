//--------------------------------------------
// NAME: Yulian Razkazov
// CLASS: XIb
// NUMBER: xxxxxxx (nomer)
// PROBLEM: #1
// FILE NAME: yulian.c
// FILE PURPOSE Domashno 1
//---------------------------------------------
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

//--------------------------------------------
// FUNCTION:puts
// Funkciqta izpisva 10te reda ot file ili stdin 
// PARAMETERS:
// int f - podava failoviq deskriptor na funkciqta
//----------------------------------------------
int printing(int b,char arg[]) {
	int i=0,r,err,f;
	char symbol;

	if(b) {
		f=open(arg,O_RDONLY,0);
		if(f==-1) {
			perror("head");
			return -1;
		}
		do
		{
			r=read(f,&symbol,1);
			if(r==-1) {
				perror("head");
				return -2;
			}
			if(symbol=='\n')
				i++;
			err=write(STDOUT_FILENO,&symbol,1);
			if(err==-1) {
				perror("head");
				return -3;
			}
		}
		while((i<10) && (r));
		err=close(f);
		if(err==-1) {
			perror("head");
			return -4;
		}
	}
	else {
		do
		{
			r=read(STDIN_FILENO,&symbol,1);
			if(r==-1) {
				perror("head");
				return -2;
			}
			if(symbol=='\n')
				i++;
			err=write(STDOUT_FILENO,&symbol,1);
			if(err==-1) {
				perror("head");
				return -3;
			}
		}
		while((i<10) && (r));
	}
	return 1;
}

int main(int argc,char* argv[]) {
	int err,i;
	char symbol,header1[3]={'=','=','>'},header2[4]={'<','=','=','\n'};

	if(argc>1) {
		if(argc==2) {
			err=printing(1,argv[1]);
			if(err<0) {
				perror("head");
				return err;
			}
		}
		else {
			i=1;
			while(i<argc) {
				if(*argv[i]=='-') {
						err=printing(0,"");
						if(err<0) {
							perror("head");
							return err;
						}
				}
				else {
					err=write(STDOUT_FILENO,header1,3);
					if(err==-1) {
						perror("head");
						return -3;
					}
					err=write(STDOUT_FILENO,argv[i],strlen(argv[i]));
					if(err==-1) {
						perror("head");
						return -3;
					}
					err=write(STDOUT_FILENO,header2,4);
					if(err==-1) {
						perror("head");
						return -3;
					}
					err=printing(1,argv[i]);
					if(err<0) {
						perror("head");
						return err;
					}
					err=write(STDOUT_FILENO,"\n",1);
					if(err==-1) {
						perror("head");
						return -3;
					}
				}
				i++;
			}
		}
	}
	else {
		err=printing(0,"");
		if(err<0) {
			perror("head");
			return err;
		}
	}
	return 0;
}

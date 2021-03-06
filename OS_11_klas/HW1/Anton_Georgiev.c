//--------------------------------------------
// NAME: Anton Georgiev
// CLASS: XIa
// NUMBER: 3
// PROBLEM: #1
// FILE NAME: Anton_Georgiev.c
// FILE PURPOSE Domashno 1 Vtori opit
//---------------------------------------------
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//--------------------------------------------
// FUNCTION:error
// Funkciqta proverqva za greshki i ako ima takiva
// gi izpisva na stdin 
// PARAMETERS:
// int c - podava varnatata stoinost ot funkciqta writer
// za da se opredeli koq ot funkciite(read,write...) dava greshka
//----------------------------------------------
int error(int c) {
	if(c<0) {
		perror("head");
		return 1;//vrashta true-ima greshka
	}
	else return 0;
}

//--------------------------------------------
// FUNCTION:writer
// Funkciqta izpisva 10te reda ot file ili stdin 
// PARAMETERS:
// int f - podava failoviq deskriptor na funkciqta
//----------------------------------------------
int writer(int f) {
	int i=0,p,c;
	char symbol;

	do
	{
		p=read(f,&symbol,sizeof(char));
		if(error(p))
			return -2;
		if(symbol=='\n')
			i++;
		c=write(STDOUT_FILENO,&symbol,sizeof(char));
		if(error(c))
			return -3;
	}
	while((i<10) && (p));
}

int main(int argc,char* argv[]) {
	int f,c,j;
	char symbol,header1[3]={'=','=','>'},header2[4]={'<','=','=','\n'};

	//proverqvam dali ima argumenti
	if(argc>1) {
		//i dali e edin ili poveche
		if(argc==2) {						//ako argumentat e edin
			f=open(argv[1],O_RDONLY,0);		//otvarqm faila i
			if(error(f))					//proverqvam za greshki
				return -1;					//
			c=writer(f);					//izpisvam
			if(error(c))					//
				return c;					//
			c=close(f);						//
			if(error(c))					//
				return -4;					//
		}
		//ako argumentite sa poveche gi broq s j i cikul while
		else {
			j=1;
			while(j<argc) {
				//proverqvam dali argumentat e - za da izpolzvam writer s stdin
				if(*argv[j]=='-') {
						c=writer(STDIN_FILENO);
						if(error(c))
							return c;
				}
				else {
					//ako ne e - si otvarqm fail
					f=open(argv[j],O_RDONLY,0);
					if(error(f)) {
						j++;
						c=write(STDOUT_FILENO,"\n",sizeof(char));
						if(error(c))
							return -3;
						continue;
					}
					c=write(STDOUT_FILENO,header1,sizeof(char)*3);
					if(error(c))
						return -3;
					c=write(STDOUT_FILENO,argv[j],strlen(argv[j]));
					if(error(c))
						return -3;
					c=write(STDOUT_FILENO,header2,sizeof(char)*4);
					if(error(c))
						return -3;
					c=writer(f);
					if(error(c))
						return c;
					c=close(f);
					if(error(c))
						return -4;
				}
				c=write(STDOUT_FILENO,"\n",sizeof(char));
				if(error(c))
					return -3;
				j++;
			}
		}
	}
	//ako nqma argumenti stdin
	else {
		c=writer(STDIN_FILENO);
		if(error(c))
			return c;
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int slen(char *red)
{
 int i=0;
 while(red[i]!='\0')
{
 i++;
}
 return i;
}

int main(int argc, char *argv[])
{
char *pat;
char *filei;
int r=0;
int j=0;
extern char *optarg;
int tek_par;

 while ((tek_par=getopt(argc, argv , "nf:p:"))!=-1)
{
 switch(tek_par)
{
 case 'p':
 pat=optarg;
 break;
 case 'f':
 filei=optarg;
 break;
 case 'n':
 j=1;
 break;
}
}

FILE* fp=fopen(filei, "r");
if(fp==NULL)
{
 printf("File %s can't be opened.\n", filei);
 return -1;
}
 char red[255];
 while(fgets(red, 255, fp)!=NULL)
{
 int i;
 int pc=0;
 int found=0;
 r++;
 for(i=0;i<slen(red);i++)
 {
 if(red[i]==pat[pc])
{
 pc++;
 if(pc==slen(pat))
{
 found=1;
 break;
}
}
 else
{
 pc=0;
}
}
 if(found)
{
 if (j==1) 
{
 printf("%d ", r);
}
 printf("%s", red);
}
}
 fclose(fp);
 return 0;
}

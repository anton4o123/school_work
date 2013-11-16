#include <stdio.h>
#include <stdlib.h>

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
int i;
char *pat;
char *filei;
char red[255];
int r=0;
int j=0;

for(i=1;i<argc;i++)
{
char *tek_par=*(argv+i);
char *sled_par=*(argv+i+1);

 if(tek_par[0]=='-')
 {
  switch(tek_par[1])
 {
  case 'p':
  pat=sled_par;
  break;
  case 'f':
  filei=sled_par;
  break;
  case 'n':
  j=1;
  break;
 }
 }
}

FILE* fp=fopen(filei, "r");
if(fp==NULL)
{
 printf("File %s can't be opened.\n", filei);
 return -1;
}

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

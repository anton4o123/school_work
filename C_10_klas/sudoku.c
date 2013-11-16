#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void devet(int s[],int b)
{
int i;

for(i=0;i<9;i++)
{
s[b*9+i]=rand()/(RAND_MAX/9)+1;
if(i)
if(s[i]==s[i-1])
while(s[i]==s[i-1])
s[b*9+i]=rand()/(RAND_MAX/9)+1;
}
}

void main()
{
srand(time(NULL));
int s[81],b,i,j;

for(b=0;b<9;b++)
{
devet(s,b);
for(b=0;b<9;b++)
{
printf("\n");
for(i=0;i<2;i++)
{
printf(" ");
for(j=0;j<2;j++)
printf("%d ",s[b*9+i*3+j]);
}
}
}
}

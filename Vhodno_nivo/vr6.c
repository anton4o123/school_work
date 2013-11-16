#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main()
{
int x,x1[100],c,i,j;
srand((unsigned)time(NULL));

do
{
printf("Molq vavedete chislo:");scanf("%d",&x);
}
while((x<1)||(x>9));
for(i=0;i<100;i++)
x1[i]=rand()/(RAND_MAX/100);
for(i=0;i<100;i++)
if(x1[i]%10==x)
{
c=x1[0];
x1[0]=x1[i];
x1[i]=c;
c=x1[99];
for(j=99;j>=1;j--)
x1[j]=x1[j-1];
x1[0]=c;
}
for(i=0;i<100;i++)
printf("%d\n",x1[i]);
}

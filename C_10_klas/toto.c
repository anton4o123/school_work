#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sorted(int p[],int d)
{
int i,j,c;

for(i=0;i<d;i++)
for(j=0;j<d-i;j++)
{
if (p[j]>p[j+1])
{
c=p[j+1];
p[j+1]=p[j];
p[j]=c;
}
}
}

void main()
{
int i,p[6];
srand((unsigned)time(NULL));

printf("Natisnete koito i da e buton!!!");getchar();
p[0]=rand()/(RAND_MAX/49)+1;
do
p[1]=rand()/(RAND_MAX/49)+1;
while(p[1]==p[0]);
do
p[2]=rand()/(RAND_MAX/49)+1;
while((p[2]==p[0])||(p[2]==p[1]));
do
p[3]=rand()/(RAND_MAX/49)+1;
while((p[3]==p[0])||(p[3]==p[1])||(p[3]==p[2]));
do
p[4]=rand()/(RAND_MAX/49)+1;
while((p[4]==p[0])||(p[4]==p[1])||(p[4]==p[2])||(p[4]==p[3]));
do
p[5]=rand()/(RAND_MAX/49)+1;
while((p[5]==p[0])||(p[5]==p[1])||(p[5]==p[2])||(p[5]==p[3])||(p[5]==p[4]));
sorted(p,6);
printf("%d,",p[0]);
printf("%d,",p[1]);
printf("%d,",p[2]);
printf("%d,",p[3]);
printf("%d,",p[4]);
printf("%d,\n",p[5]);
}

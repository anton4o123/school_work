#include <stdio.h>

void main()
{
int x,y,i,j;

printf("Molq vavedete dolna granica:");scanf("%d",&x);
do
{
printf("Molq vavedete gorna granica:");scanf("%d",&y);
}
while(y<=x);

for(i=x;i<y;i++)
for(j=2;j<=i;j++)
{
if(i%j==0)
{
if(i!=j)
break;
else
if(i%10==3)
printf("%d\n",i);
}
}
}

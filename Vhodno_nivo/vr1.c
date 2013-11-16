#include <stdio.h>

void main()
{
int x,y,z=0,i;

printf("Molq vavedete dolna granica:");scanf("%d",&x);
y=x;
do
{
printf("Molq vavedete gorna granica:");scanf("%d",&y);
}
while(y<=x);
for(i=x;i<y;i++)
if(i%2)
z=z+i;
printf("Sbora na vsichki nechetni chisla v intervala e:%d\n",z);
}

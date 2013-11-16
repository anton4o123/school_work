#include <stdio.h>

int fibo(int a)
{
int i=2,b,m=1,n=1;

if((a==1)||(a==2))
return 1;
else
{
do
{
b=m+n;
n=m;
m=b;
i++;
}
while(i<=a);
return b;
}
}

void main()
{
int x,y,z=0,c,i=1;

printf("Molq vavedete dolna granica:");scanf("%d",&x);
do
{
printf("Molq vavedete gorna granica:");scanf("%d",&y);
}
while(y<=x);
do
{
c=fibo(i);
if((c>=x)&&(c<=y))
z=z+c;
i++;
}
while(c<y);
printf("Sbora na chislata na fibonachi v intervala e:%d\n",z);
}

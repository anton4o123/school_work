#include <stdio.h>

int fibo(long long int a)
{
long long int i=2,b,m=1,n=1;

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
long long int x,i=1,x1[10],c,j=0;

do
{
printf("Molq vavedete chislo:");scanf("%lld",&x);
}
while((x<0)||(x>9));

do
{
c=fibo(i);
if(c%x==0)
{
x1[j]=c;
j++;
}
i++;
}
while(j<10);
for(i=0;i<10;i++)
printf("%lld\n",x1[i]);
}

#include <stdio.h>

void main()

{
unsigned long long x,y;
int i;
int a,b;

printf("Vavedete obsht broi:");
scanf("%d",&a);
printf("Vavedete izbran broi:");
scanf("%d",&b);
x=1;
y=1;
i=a;
while (i>a-b)
{
x=x*i;
i--;
}
for (i=2;i<=b;++i)
y=y*i;
x=x/y;
printf("Broqt na kombinaciite e:%lld\n",x);
}

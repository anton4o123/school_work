#include <stdio.h>

float fact(int a)
{
float o;
int i;

o=(float)a;
for(i=1;i<a;i++)
o=o*((float)a-(float)i);
return(o);
}

void main()
{
int a;
float o;

printf("Vavedete chislo:");scanf("%d",&a);
o=fact(a);
printf("%.0f\n",o);
}

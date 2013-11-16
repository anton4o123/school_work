#include <stdio.h>

void main()
{
unsigned int mask,bit,n;

printf("Vavedete chislo:");scanf("%u",&n);
printf("Vavedete bit:");scanf("%u",&bit);
mask=1;
mask=mask<<(bit-1);
if (n&mask)
n=n^mask;
printf("Chisloto e:%d\n",n);
}

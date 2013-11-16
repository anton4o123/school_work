#include <stdio.h>

void main()
{
unsigned int mask=1,n,bit;

printf("Vavedete chislo:");scanf("%u",&n);
printf("Vavedete bit:");scanf("%u",&bit);
mask=mask<<(bit-1);
n=n^mask;
printf("Novoto chislo e:%d\n",n);
}

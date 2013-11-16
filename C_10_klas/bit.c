#include <stdio.h>

void main()
{
unsigned int mask=1,bit,n;


printf("Vavedete chislo:");scanf("%u",&n);
printf("Vavedete bit:");scanf("%d",&bit);
mask=mask<<(bit-1);
if (n&mask)
printf("Bita e 1\n");
else printf("Bita e 0\n");
}

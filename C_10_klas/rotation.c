#include <stdio.h>

void main()
{
unsigned int mask,brot,n,bit,kont;

printf("Vavedete chislo:");scanf("%u",&n);
printf("Vavedete broi na rotacii na lqvo:");scanf("%u",&brot);
kont=1;
do
{
mask=1;
mask=mask<<7;
if (n&mask)
bit=1;
else bit=0;
n=n<<1;
if (bit)
{
mask=mask<<1;
n=n^mask;
mask=1;
n=n^mask;
}
kont++;
}
while (kont<=brot);
printf("Novoto chislo e:%d\n",n);
}

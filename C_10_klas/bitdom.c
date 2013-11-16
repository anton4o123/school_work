#include <stdio.h>

int check(unsigned int n,unsigned int bit)
{
unsigned int mask=1;
mask<<(bit-1);
if (n&mask)
return 1;
else return 0;
}

int rotatel(unsigned int n,unsigned int bit)
{
unsigned int mask=1,mask2=1<<8,izhod,c;

c=1;
izhod=n;
do
{
if (check(izhod,8))
{
izhod=izhod<<1;
izhod=izhod^mask2;
izhod=izhod^mask;
}
else izhod=izhod<<1;
c++;
}
while (c<=bit);
return izhod;
}

int rotater(unsigned int n,unsigned int bit)
{
int mask=1<<7,izhod,c;

c=1;
izhod=n;
do
{
if (check(izhod,1))
{
izhod=izhod>>1;
izhod=izhod^mask;
}
else izhod=izhod>>1;
c++;
}
while (c<=bit);
return izhod;
}


void main()
{
unsigned int mask=1,n,bit,izhod,kontrol;

do
{
printf("Vavedete 0<chislo<256:");scanf("%d",&n);
}
while ((n<1) && (n>255));
do
{
printf("Vavedete 0<bit<33:");scanf("%d",&bit);
}
while ((bit<1) && (bit>32));
do
{
printf("Vavedete 1 za rotaciq na lqvo ili 2 za rotaciq na dqsno:");
scanf("%d",&kontrol);
}
while ((kontrol<1) && (kontrol>2));

mask=mask<<(bit-1);
izhod=n^mask;
printf("Vavedenoto chislo s invertiran vaveden bit:%d\n",izhod);

izhod=n|mask;
printf("Vavedenoto chislo s vdignat vaveden bit:%d\n",izhod);

mask=~mask;
izhod=n&mask;
printf("Vavedenoto chislo s smaknat vaveden bit:%d\n",izhod);

if (kontrol==1)
izhod=rotatel(n,bit);
else izhod=rotater(n,bit);
printf("Vavedenoto chislo rotirano s broi raven na vaveden bit:");
printf("%d\n",izhod);
}

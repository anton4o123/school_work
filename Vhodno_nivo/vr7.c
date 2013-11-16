#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main()
{
srand((unsigned)time(NULL));
int x,x1[10],x2[5];

do
{
printf("Molq vavedete chislo:");scanf("%d",&x);
}
while((x<1)||(x>99));

for

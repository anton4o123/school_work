#include <stdio.h>

typedef struct
{
int x;
int y;
}point;

int calcarea(point p1,point p2)
{
return((p2.x-p1.x)*(p2.y-p1.y));
}

void main()
{
point p1,p2;

printf("Vavedete koordinatite na parvata tochka:");
scanf("%d%d",&p1.x,&p1.y);
printf("Vavedete koordinatite na vtorata tochka:");
scanf("%d%d",&p2.x,&p2.y);
printf("Liceto na pravoagalnika e:%d\n",calcarea(p1,p2));
}

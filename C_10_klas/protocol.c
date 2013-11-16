#include <stdio.h>

void main()
{
float ri[8],u[8],i[8],rd[8],rv[8],de[8],e[8],p[8],pd[8],de2[8],e2[8];
int a;

for(a=0;a<7;a++)
{
printf("Vavedete naprejenie:");
scanf("%f",&u[a]);
}
for(a=0;a<7;a++)
{
printf("Vavedete tok:");
scanf("%f",&i[a]);
}
for(a=0;a<7;a++)
{
printf("Vavedete r volt:");
scanf("%f",&rv[a]);
}
for(a=0;a<7;a++)
rd[a]=u[a]/(i[a]-u[a]/rv[a]);
for(a=0;a<7;a++)
ri[a]=u[a]/i[a];
for(a=0;a<7;a++)
de[a]=ri[a]-rd[a];
for(a=0;a<7;a++)
e[a]=(de[a]/rd[a])*100;
for(a=0;a<7;a++)
p[a]=u[a]*i[a];
for(a=0;a<7;a++)
pd[a]=u[a]*(i[a]-u[a]/rv[a]);
for(a=0;a<7;a++)
de2[a]=p[a]-pd[a];
for(a=0;a<7;a++)
e2[a]=(de2[a]/pd[a])*100;

for(a=0;a<7;a++)
printf("rd:%f\n",rd[a]);
for(a=0;a<7;a++)
printf("de:%f\n",de[a]);
for(a=0;a<7;a++)
printf("e:%f\n",e[a]);
for(a=0;a<7;a++)
printf("p:%f\n",p[a]);
for(a=0;a<7;a++)
printf("pd:%f\n",pd[a]);
for(a=0;a<7;a++)
printf("de2:%f\n",de2[a]);
for(a=0;a<7;a++)
printf("e2:%f\n",e2[a]);
for(a=0;a<7;a++)
printf("ri:%f\n",ri[a]);
}

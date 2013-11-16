#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void kart(int k[])
{
int i,j;

for(i=0;i<52;i++)
{
k[i]=rand()/(RAND_MAX/52)+1;
if(i)
{
j=0;
while(j<i)
{
if(k[i]==k[j])
{
k[i]=rand()/(RAND_MAX/52)+1;
j=0;
continue;
}
j++;
}
}
}
}

void himikal(int p1[],int p2[],int *p12,int *p22,int i)
{
int c;

printf("\n");
printf("\n");
printf("\n");
if((p1[i]>0)&&(p1[i]<14))
{
if(p1[i]<10){c=p1[i]+1;printf("               %d",c);}
if(p1[i]==10)printf("               J");
if(p1[i]==11)printf("               Q");
if(p1[i]==12)printf("               K");
if(p1[i]==13)printf("               A");
printf("  PIKA");
*p12=0;
}else
if((p1[i]>13)&&(p1[i]<27))
{
if(p1[i]-13<10){c=p1[i]-12;printf("               %d",c);}
if(p1[i]-13==10)printf("               J");
if(p1[i]-13==11)printf("               Q");
if(p1[i]-13==12)printf("               K");
if(p1[i]-13==13)printf("               A");
printf("  KUPA");
*p12=13;
}else
if((p1[i]>26)&&(p1[i]<40))
{
if(p1[i]-26<10){c=p1[i]-25;printf("               %d",c);}
if(p1[i]-26==10)printf("               J");
if(p1[i]-26==11)printf("               Q");
if(p1[i]-26==12)printf("               K");
if(p1[i]-26==13)printf("               A");
printf("  KARO");
*p12=26;
}
else
{
if(p1[i]-39<10){c=p1[i]-38;printf("               %d",c);}
if(p1[i]-39==10)printf("               J");
if(p1[i]-39==11)printf("               Q");
if(p1[i]-39==12)printf("               K");
if(p1[i]-39==13)printf("               A");
printf("  SPATIQ");
*p12=39;
}
if((p2[i]>0)&&(p2[i]<14))
{
if(p2[i]<10){c=p2[i]+1;printf("     %d",c);}
if(p2[i]==10)printf("     J");
if(p2[i]==11)printf("     Q");
if(p2[i]==12)printf("     K");
if(p2[i]==13)printf("     A");
printf("  PIKA");
*p22=0;
}
else
if((p2[i]>13)&&(p2[i]<27))
{
if(p2[i]-13<10){c=p2[i]-12;printf("     %d",c);}
if(p2[i]-13==10)printf("     J");
if(p2[i]-13==11)printf("     Q");
if(p2[i]-13==12)printf("     K");
if(p2[i]-13==13)printf("     A");
printf("  KUPA");
*p22=13;
}
else
if((p2[i]>26)&&(p2[i]<40))
{
if(p2[i]-26<10){c=p2[i]-25;printf("     %d",c);}
if(p2[i]-26==10)printf("     J");
if(p2[i]-26==11)printf("     Q");
if(p2[i]-26==12)printf("     K");
if(p2[i]-26==13)printf("     A");
printf("  KARO");
*p22=26;
}
else
{
if(p2[i]-39<10){c=p2[i]-38;printf("     %d",c);}
if(p2[i]-39==10)printf("     J");
if(p2[i]-39==11)printf("     Q");
if(p2[i]-39==12)printf("     K");
if(p2[i]-39==13)printf("     A");
printf("  SPATIQ");
*p22=39;
}
}

void pe(int p1[],int p2[],int *b1,int *b2)
{
int j,c;

c=p1[0];
for(j=0;j<*b1-1;j++)
p1[j]=p1[j+1];
p1[*b1-1]=c;
p1[*b1]=p2[0];
p1[*b1+1]=0;
for(j=0;j<*b2-1;j++)
p2[j]=p2[j+1];
p2[*b2-1]=0;
*b1=*b1+1;
*b2=*b2-1;
}

void pd(int p1[],int p2[],int *b1,int *b2)
{
int j,c;

c=p2[0];
for(j=0;j<*b2-1;j++)
p2[j]=p2[j+1];
p2[*b2-1]=c;
p2[*b2]=p1[0];
p2[*b2+1]=0;
for(j=0;j<*b1-1;j++)
p1[j]=p1[j+1];
p1[*b1-1]=0;
*b1=*b1-1;
*b2=*b2+1;
}

void voina(int p1[],int p2[],int *b1,int *b2,int *p12,int *p22,int i)
{
printf("\n                   VOINA!!!\n\n");
i++;
getchar();
himikal(p1,p2,p12,p22,i);
i++;
getchar();
himikal(p1,p2,p12,p22,i);
i++;
getchar();
himikal(p1,p2,p12,p22,i);
if(p1[i]-*p12>p2[i]-*p22)
{
pe(p1,p2,b1,b2);
pe(p1,p2,b1,b2);
pe(p1,p2,b1,b2);
pe(p1,p2,b1,b2);
getchar();
}else
if(p1[i]-*p12<p2[i]-*p22)
{
pd(p1,p2,b1,b2);
pd(p1,p2,b1,b2);
pd(p1,p2,b1,b2);
pd(p1,p2,b1,b2);
getchar();
}else voina(p1,p2,b1,b2,p12,p22,i);
}

void rez(int b1,int b2)
{
printf("                Player1:%d    Player2:%d\n",b1,b2);
}

void main()
{
int i,b1=26,b2=26,k[52],p1[52],p2[52],p12,p22;
srand((unsigned)time(NULL));

kart(k);
for(i=0;i<26;i++)
{
p1[i]=k[i];
p2[i]=k[i+26];
}
getchar();
do
{
i=0;
system("clear");
rez(b1,b2);
himikal(p1,p2,&p12,&p22,i);
printf("\n");
getchar();
if(p1[i]-p12>p2[i]-p22)
pe(p1,p2,&b1,&b2);
else
if(p1[i]-p12<p2[i]-p22)
pd(p1,p2,&b1,&b2);
else voina(p1,p2,&b1,&b2,&p12,&p22,i);
}
while((b1!=0)&&(b2!=0));
system("clear");
rez(b1,b2);
if(b1==0)
printf("\n\n                         POBEDITEL E PLAYER2!!!\n");
else printf("\n\n                         POBEDITEL E PLAYER1\n");
}

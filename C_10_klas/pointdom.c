#include <stdio.h>
#include <string.h>

int len(char n[])
{
char *l;
int i;

l=n-1;;
i=-1;
do
{
i++;
l++;
}
while(*l!=0);
return i;
}

int cmp(char n[],char n2[])
{
char *s,*s2;
int r;

s=n;
s2=n2;
r=1;
do
{
if(*s!=*s2)
r=0;
s++;
s2++;
}
while((*s!=0) || (r==1));
return r;
}

void cat(char n[],char n2[])
{
char *c,*c2;

c=n;
c2=n2;
while(*c!=0)
c++;
while(*c2!=0)
{
*c=*c2;
c++;
c2++;
}
}

void main()
{
char n[100],n2[100];

printf("Vavedete parvi niz za proverka i obrabotka:");gets(n);
printf("Vavedete vtori niz za proverka i obrabotka:");gets(n2);
printf("Broqt na simvolite v parvi niz e:%d\n",len(n));
printf("Broqt na simvolite v vtori niz e:%d\n",len(n2));
if(cmp(n,n2)==1)
printf("Nizovete sa ednakvi!!!\n");
else printf("Nizovete sa razlichni!!!\n");
cat(n,n2);
printf("Obedinenite nizove sa:%s\n",n);
}

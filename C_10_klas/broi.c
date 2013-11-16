#include <stdio.h>
#include <string.h>

int main()
{
int l,i,m,g,c,spa;
char s[100];

printf("Napishi neshto:");gets(s);
l=strlen(s);
m=0;
g=0;
c=0;
spa=0;
for (i=0;i<l;i++)
{
if ((s[i]>='a') && (s[i]<='z'))
m=++m;
if ((s[i]>='A') && (s[i]<='Z'))
g=++g;
if ((s[i]>='0') && (s[i]<='9'))
c=++c;
if (s[i]==' ')
spa=++spa;
}
printf("Broqt na malkite bukvi e:%d\n",m);
printf("Broqt na golemite bukvi e:%d\n",g);
printf("Broqt na cifrite e:%d\n",c);
printf("Broqt na intervalite e:%d\n",spa);
return 0;
}

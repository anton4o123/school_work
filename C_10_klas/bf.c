#include <stdio.h>
#include <string.h>

void bf(char s[],char ss[])
{
int i,j=0;

while(1)
{
if(ss[j]=='\0')
break;
for(i=97;i<123;i++)
if(ss[j]==i)
s[j]=i;
j++;
}
}

void main()
{
char s[10],ss[10];

printf("Vavedete parola:");gets(ss);
bf(s,ss);
printf("Parolata e:%s\n",s);
}

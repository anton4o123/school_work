#include <stdio.h>

typedef struct
{
char imena[25],klas[5];
float sru;
}uch;

int sr(const void *a,const void *b)
{
return(strcmp((((uch*)a)->imena),(((uch*)b)->imena)));
}

void main()
{
int i,go;
uch koi[100];
FILE* f;

printf("Vavedete broqt na uchenicite:");scanf("%d",&go);
for(i=0;i<go;i++)
{
getchar();
printf("Vavedete imenata na uchenik N:%d:",i+1);gets(koi[i].imena);
printf("Vavedete klasa na uchenik N:%d:",i+1);gets(koi[i].klas);
printf("Vavedete sr. uspeh na uchenik N:%d:",i+1);
scanf("%f",&koi[i].sru);
printf("\n");
}
qsort(koi,go,sizeof(uch),sr);
printf("\n");
for(i=0;i<go;i++)
{
printf("Imenata na uchenik N:%d sa:%s\n",i+1,koi[i].imena);
printf("Klasat na uchenik N:%d e:%s\n",i+1,koi[i].klas);
printf("Sredniqt uspeh na uchenik N:%d e:%.2f\n\n",i+1,koi[i].sru);
}
f=fopen("bin.bin","wb");
fwrite(&go,sizeof(int),1,f);
for(i=0;i<go;i++)
fwrite(&koi[i],sizeof(uch),go,f);
fclose(f);
}

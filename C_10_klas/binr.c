#include <stdio.h>

typedef struct
{
char imena[50],klas[5];
float sru;
}uch;

int sr(const void *a,const void *b)
{
return(strcmp((((uch*)a)->sru),(((uch*)b)->sru)));
}

void main()
{
int i,go;
uch koi[100];
FILE *f;

f=fopen("bin.bin","rb");
fread(&go,sizeof(int),1,f);
fread(&koi,sizeof(uch),go,f);
fclose(f);
qsort(koi,go,sizeof(uch),sr);
f=fopen("bin.txt","wt");
for(i=0;i<go;i++)
{
fprintf(f,"Imenata na uchenik N:%d sa:%s\n",i+1,koi[i].imena);
fprintf(f,"Klasat na uchenik N:%d e:%s\n",i+1,koi[i].klas);
fprintf(f,"Sredniqt uspeh na uchenik N:%d e:%.2f\n\n",i+1,koi[i].sru);
}
fclose(f);
}

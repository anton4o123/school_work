#include <stdio.h>

void main() {
	int a=5;
	int* p1;
	int* p2;
	int* p3;
	int* p4;
	
	p1=&a;
	p2=p1+1;
	p3=p2+1;
	p4=p3+1;
	
	printf("%p\n",p1);
	printf("%d\n",*p1);
	printf("%p\n",p2);
	printf("%d\n",*p2);
	printf("%p\n",p3);
	printf("%d\n",*p3);
	printf("%p\n",p4);
	printf("%d\n",*p4);
}

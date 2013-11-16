#include <stdio.h>
#include <unistd.h>

void main()
{
	unsigned long long int sum=0,n;

	printf("Molq vavedete stapkata:");scanf("%lld",&n);
	while(1)
	{
		sum+=n;
		sleep(0);
		printf("%lld\n",sum);
	}
}

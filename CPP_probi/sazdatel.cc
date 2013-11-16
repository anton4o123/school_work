#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main()
{
	int x[2][882],j=0;

	for(int i=0;i<120;i++)
	{
		x[0][i]=rand()/(RAND_MAX/21)-10;
		x[1][i]=rand()/(RAND_MAX/21)-10;
		if(i)
		{
			j=0;
			while(j<i)
			{
				if((x[0][i]==x[0][j])&&(x[1][i]==x[1][j]))
				{
					x[0][i]=rand()/(RAND_MAX/21)-10;
					x[1][i]=rand()/(RAND_MAX/21)-10;
					j=0;
					continue;
				}
				j++;
			}
		}
	}

	for(int i=0;i<120;i++)
	{
		int p=-(x[0][i]+x[1][i]);
		int q=x[0][i]*x[1][i];
		cout << "x*x+" << p << "*x+" << q << endl;
	}
}

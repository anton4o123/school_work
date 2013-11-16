#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
	int i=0;

	cout << "Molq vavedete puls:";cin >> i;
	while(1)
	{
		sleep(1);
		cout << "\7";
	}
return 0;
}

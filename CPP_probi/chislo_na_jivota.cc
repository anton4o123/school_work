#include <iostream>
using namespace std;

int main()
{
	int d,m,g,r;

	cout << "Molq vavedete data na rajdane:";cin >> d;
	cout << "Molq vavedete mesec na rajdane:";cin >> m;
	cout << "Molq vavedete godina na rajdane:";cin >> g;

	d=d%10+d/10;
	m=m%10+m/10;
	r=g%10;
	g=g/10;
	r+=g%10;
	g=g/10;
	r+=g%10+g/10+m+d;

	if(r/10)
		r=r%10+r/10;
	if(r==10)
		r=1;

	cout << "Vasheto chislo na jivota e:" << r << "" << endl;

	return 0;
}

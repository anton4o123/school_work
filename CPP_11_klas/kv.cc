#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	int a,b,c,x1,x2,d;

	cout << "Molq vavedete 'a':";cin >> a;
	cout << "Molq vavedete 'b':";cin >> b;
	cout << "Molq vavedete 'c':";cin >> c;

	d=((b*b)-(4*a*c));
	x1=((-b-sqrt(d))/(2*a));
	x2=((-b+sqrt(d))/(2*a));

	cout << "X1=" << x1;
	cout << "X2=" << x2 << endl;

	return 0;
}

#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	int a=0,b=0,c=0,x1=0,x2=0,d=0;

	cout << "Molq vavedete 'a':";cin >> a;
	cout << "Molq vavedete 'b':";cin >> b;
	cout << "Molq vavedete 'c':";cin >> c;

	d=(b*b)-(4*a*c);
	if(d>=0)
	{
	d=sqrt(d);
	x1=((-b)-(d))/(2*a);
	x2=((-b)+(d))/(2*a);
	cout << "x1:" << x1 << endl;
	cout << "x2:" << x2 << endl;
	}else cout << "Uravnenieto nqma reshenie!!!" << endl;
	return 0;
}

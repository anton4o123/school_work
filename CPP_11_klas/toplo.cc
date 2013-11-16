#include <iostream>
#include <list>
using namespace std;

void print_all(list<int>& l) {
	for(list<int>::iterator it=l.begin();
		it!=l.end();++it) {
		cout << (*it) << ' ';
	}
	cout << endl;
}

int main()
{
	list<int> l(5,1);
	print_all(l);

	int i=1;
	while(i) {
	for(unsigned int j=0;i<65536;i++)
		l.insert(l.end(),1);
	for(unsigned int j=65535;j>=0;j--)
		l.erase(l.begin());
	}
return 0;
}

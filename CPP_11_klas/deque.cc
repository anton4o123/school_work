#include <iostream>
#include <deque>
using namespace std;

void print_all(deque<int>& d) {
	for(deque<int>::iterator it=d.begin();
		it!=d.end();++it) {
		cout << (*it) << ' ';
	}
	cout << endl;
}

int main()
{
	deque<int> d;
	cout << "d.empty(): " << d.empty() << endl;
	
	d.push_back(3);
	d.push_back(4);
	print_all(d);
	
	d.push_front(2);
	d.push_front(1);
	print_all(d);
	
	d.insert(d.end(),1);
	print_all(d);

	d.erase(d.end());
	print_all(d);




return 0;
}

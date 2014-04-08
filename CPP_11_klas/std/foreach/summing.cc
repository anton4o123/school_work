#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

class sum {
	int value_;
public:
	sum()
	: value_(0) {}
	
	int value() const {
		return value_;
	}
	
	void operator()(int val) {
		value_+=val;
	}
};

class mul {
	int value_;
public:
	mul()
	: value_(1) {}
	
	int value() const {
		return value_;
	}
	
	void operator()(int val) {
		value_*=val;
	}
};

int main() {
	int a[] = {10, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	list<int> l(a, a+10);
	
	sum s=for_each(l.begin(), l.end(), sum());
	cout << s.value() << endl;
	
	mul m=for_each(l.begin(), l.end(), mul());
	cout << m.value() << endl;

	return 0;
}

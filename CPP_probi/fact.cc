#include <iostream>
using namespace std;

class fact {
	long long int a;
public:
	fact(long long int b=0)
	:a(b) {}

	long long int get_fact() const {
		return a;
	}

	void set_fact(long long int b) {
		a=b;
	}

	fact operator-(long long int& b) {
		fact res;
		res.set_fact(a-b);
		return res;
	}
};

fact operator*=(fact& a,fact& b) {
		a.set_fact(a.get_fact()*b.get_fact());
		return a;
	}

fact operator!(fact& a) {
	fact b,c;
	b.set_fact(1);
	for(long long int i=0;i<a.get_fact();i++) {
		c=a-i;
		b*=c;
	}
	return b;
}

int main()
{
	fact a(30),b;

	b=!a;
	cout << b.get_fact() << endl;


	return 0;
}

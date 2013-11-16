#include <iostream>
using namespace std;

class Point {
	double x_,y_;
public:

	Point(double x=0.0,double y=0.0)
	: x_(x),y_(y)
	{}

	double get_x() const {
		//const Point* const this
		
		return this -> x_;
		//return x_;
	}
	double get_y() const {
		return this -> y_;
	}
	
	void bar(Point* p) {
		//this=p;
		//Point * const this
	}
	
	Point& set_x(double x) {
		x_=x;
		return *this;
	}
	
	Point& set_y(double y) {
		y_=y;
		return *this;
	}
};

int main()
{
	int a;
	a=0;
	
	const int b=0;
	//b=1;	
	
	const Point p0(2.0,2.0);
	Point p1,p2;
	
	//p0.bar(&p1);
	
	cout << "x=" << p0.get_x() << ";y=" << p0.get_y() << endl;
	cout << "x=" << p1.get_x() << ";y=" << p1.get_y() << endl;
	cout << "x=" << p2.get_x() << ";y=" << p2.get_y() << endl;
	
	Point p3(3.0);
	
	p3.set_x(42);
	p3.set_y(43);
	
	(p3.set_x(44)).set_y(45);
	
	cout << "x=" << p3.get_x() << ";y=" << p3.get_y() << endl;

	return 0;
}

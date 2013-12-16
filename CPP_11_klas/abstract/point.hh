#ifndef POINT_HH_
#define POINT_HH_
#include <iostream>


class Point {
	double x_,y_;
public:
	Point(int x,int y)
	: x_(x),y_(y) {}
	
	double get_x() const {
		return x_;
	}
	
	double get_y() const {
		return y_;
	}
};

std::ostream& operator<<(std::ostream& out, const Point& p);
#endif

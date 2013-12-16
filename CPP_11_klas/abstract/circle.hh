#ifndef CIRCLE_HH_
#define CIRCLE_HH_
#include "base.hh"
#include "point.hh"

class Circle: public Shape {
	double r_;
	Point o_;
public:
	Circle(const Point o,double r)
	: o_(o),r_(r) {}
	
	void draw();
};
#endif

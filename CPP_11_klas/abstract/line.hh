#ifndef LINE_HH__
#define LINE_HH__
#include "point.hh"
#include "base.hh"

class Line: public Shape {
	Point a_,b_;
public:
	Line(const Point& a,const Point& b)
	: a_(a),b_(b) {}
	
	void draw();
};
#endif

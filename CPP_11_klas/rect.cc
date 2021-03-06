#include <iostream>
#include <cmath>
using namespace std;

class Point {
	double x_,y_;
public:
	Point(double x=0.0,double y=0.0)
	: x_(x),y_(y) {}	
	
	double get_x() const {
		return this -> x_;
	}

	double get_y() const {
		return this -> y_;
	}

	void set_x(double v) {
		x_=v;
	}

	void set_y(double v) {
		y_=v;
	}
};

class Rectangle {
	Point p1_,p2_;
public:
	Rectangle(Point p1,Point p2)
	: p1_(p1),p2_(p2) {}

	Point get_p1() const {
		return this -> p1_;
	}

	Point get_p2() const {
		return this -> p2_;
	}

	void set_p1(Point p) {
		p1_.set_x(p.get_x());
		p1_.set_y(p.get_y());
	}

	void set_p2(Point p) {
		p2_.set_x(p.get_x());
		p2_.set_y(p.get_y());
	}

	double area() const {
		return abs((p2_.get_x()-p1_.get_x())*(p2_.get_y()-p1_.get_y()));
	}

	Rectangle inntersection(const Rectangle& r) const {
		Point p1,p2;
		Rectangle r2(p1,p2);

		if((((r.get_p1().get_x()>p1_.get_x())&&(r.get_p1().get_y()>p1_.get_y()))&&((r.get_p1().get_x()<p2_.get_x())&&(r.get_p1().get_y()<p2_.get_y())))&&(((r.get_p2().get_x()>p1_.get_x())&&(r.get_p2().get_y()>p1_.get_y()))&&(r.get_p2().get_x()<p2_.get_x())&&(r.get_p2().get_y()<p2_.get_y()))) {
			p1.set_x(r.get_p1().get_x());
			p1.set_y(r.get_p1().get_y());
			p2.set_x(r.get_p2().get_x());
			p2.set_y(r.get_p2().get_y());
			r2.set_p1(p1);
			r2.set_p2(p2);
			return r2;
		}

		if((((r.get_p1().get_x()<p1_.get_x())&&(r.get_p1().get_y()<p1_.get_y()))&&((r.get_p1().get_x()>p2_.get_x())&&(r.get_p1().get_y()>p2_.get_y())))&&(((r.get_p2().get_x()<p1_.get_x())&&(r.get_p2().get_y()<p1_.get_y()))&&(r.get_p2().get_x()>p2_.get_x())&&(r.get_p2().get_y()>p2_.get_y()))) {
			p1.set_x(p1_.get_x());
			p1.set_y(p1_.get_y());
			p2.set_x(p2_.get_x());
			p2.set_y(p2_.get_y());
			r2.set_p1(p1);
			r2.set_p2(p2);
			return r2;
		}

		if(((r.get_p1().get_x()>p1_.get_x())&&(r.get_p1().get_y()>p1_.get_y()))&&((r.get_p1().get_x()<p2_.get_x())&&(r.get_p1().get_y()<p2_.get_y()))) {
			p1.set_x(r.get_p1().get_x());
			p1.set_y(r.get_p1().get_y());
			p2.set_x(p2_.get_x());
			p2.set_y(p2_.get_y());
			r2.set_p1(p1);
			r2.set_p2(p2);
			return r2;
		}

		if(((r.get_p1().get_x()<p1_.get_x())&&(r.get_p1().get_y()<p1_.get_y()))&&((r.get_p1().get_x()>p2_.get_x())&&(r.get_p1().get_y()>p2_.get_y()))) {
			p1.set_x(p1_.get_x());
			p1.set_y(p1_.get_y());
			p2.set_x(r.get_p2().get_x());
			p2.set_y(r.get_p2().get_y());
			r2.set_p1(p1);
			r2.set_p2(p2);
			return r2;
		}
	}

};

int main()
{
	Point p1(1,1),p2(3,3),p3(0,0),p4(2,2);
	Rectangle r(p1,p2);
	Rectangle r2(p3,p4);
	Rectangle r3(p1,p1);

	cout << "Liceto e ravno na:" << r.area() << endl;
	cout << r.inntersection(r2).get_p1().get_x() << ",";
	cout << r.inntersection(r2).get_p1().get_y() << ";";
	cout << r.inntersection(r2).get_p2().get_x() << ",";
	cout << r.inntersection(r2).get_p2().get_y() << endl;

	return 0;
}

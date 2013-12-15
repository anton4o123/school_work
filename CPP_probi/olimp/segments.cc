#include <iostream>
using namespace std;

class Point {
	int x_;
	int y_;
public:
	Point(int x=0,int y=0)
	: x_(x),y_(y) {}

	int get_x() const {
		return x_;
	}
	
	int get_y() const {
		return y_;
	}
	
	void set_x(int val) {
		x_=val;
	}
	
	void set_y(int val) {
		y_=val;
	}
};

class Line {
	Point p1_;
	Point p2_;
public:
	Line(int x1=0,int y1=0,int x2=0,int y2=0)
	: p1_(x1,y1),p2_(x2,y2) {}

	Point get_p1() const {
		return p1_;
	}
	
	Point get_p2() const {
		return p2_;
	}
	
	void set_p1(int x,int y) {
		p1_.set_x(x);
		p1_.set_y(y);
	}
	
	void set_p2(int x,int y) {
		p2_.set_x(x);
		p2_.set_y(y);
	}
	
	bool perpendicular(Line l) {
		double slope1,slope2;
		bool perpen=false;
		
		slope1=(p1_.get_y()-p2_.get_y())/(p1_.get_x()-p2_.get_x());
		slope2=(l.get_p1().get_y()-l.get_p2().get_y())/(l.get_p1().get_x()-l.get_p2().get_x());
		
		if(slope1==-1/slope2) {
			perpen=true;
		}
		
		return perpen;
	}
};

int main() {
	int x1,y1,x2,y2,a,b;
	Line l1,l2(1,3,2,2);
		
	do {
		cin >> x1 >> y1 >> x2 >> y2 >> a >> b;
	} while(((x1<1)||(x1>=50)) || ((y1<1)||(y1>=50)) || ((x2<1)||(x2>=50)) || ((y2<1)||(y2>=50)) || ((a<1)||(a>=50)) || ((b<1)||(b>=50)));
	
	l1.set_p1(x1,y1);
	l1.set_p2(x2,y2);
	cout << l1.perpendicular(l2) << endl;
	
	return 0;
}

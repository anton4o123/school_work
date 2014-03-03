#ifndef DOT_HH__
#define DOT_HH__

#include "../headers/basic.hh"

class Dot {
	int x, y, xVel, yVel;
public:
	Dot();
	void handle_input();
	void move();
	void show();
	void set_x(int X);
	void set_y(int Y);
	int get_x();
	int get_y();
};

#endif

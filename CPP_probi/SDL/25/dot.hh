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
};

#endif

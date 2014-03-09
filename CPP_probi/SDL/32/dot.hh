#ifndef DOT_HH__
#define DOT_HH__

#include "../headers/basic.hh"

const int DOT_WIDTH=20;
const int DOT_HEIGHT=20;
const int DOT_VEL=600;

class Dot {
	float x, y, xVel, yVel;
public:
	Dot();
	void handle_input();
	void move(Uint32 deltaTime);
	void show();
};

#endif

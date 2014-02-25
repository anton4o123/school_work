#include "../headers/basic.hh"

class Dot {
	int x, y, xVel, yVel;
public:
	Dot();
	void handle_input();
	void move();
	void show();
};

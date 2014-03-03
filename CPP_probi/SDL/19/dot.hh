#ifndef DOT_HH__
#define DOT_HH__

#include "../headers/basic.hh"
#include <vector>
#include <cmath>

struct Circle {
	int x, y, r;
};

class Dot {
	int xVel, yVel;
	Circle c;
public:
	Dot();
	void handle_input();
	void move(std::vector<SDL_Rect> &rects, Circle &circle);
	void show();
};

#endif

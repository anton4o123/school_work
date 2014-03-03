#ifndef DOT_HH__
#define DOT_HH__

#include "../headers/basic.hh"
#include <vector>

class Dot {
	int x, y, xVel, yVel;
	std::vector<SDL_Rect> box;
	void shift_boxes();
public:
	Dot(int X, int Y);
	void handle_input();
	void move(std::vector<SDL_Rect> &rects);
	void show();
	std::vector<SDL_Rect> &get_rects();
};

#endif

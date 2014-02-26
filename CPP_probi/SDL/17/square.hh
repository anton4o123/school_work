#ifndef SQUARE_HH__
#define SQUARE_HH__

#include "../headers/basic.hh"

class Square {
	SDL_Rect box;
	int xVel, yVel;
public:
	Square();
	void handle_input();
	void move();
	void show();
};
#endif

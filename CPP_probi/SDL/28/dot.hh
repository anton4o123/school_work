#ifndef DOT_HH__
#define DOT_HH__

#include "particle.hh"

const int TOTAL_PARTICLES=20;

class Dot {
	int x, y, xVel, yVel;
	Particle *particles[TOTAL_PARTICLES];
public:
	Dot();
	~Dot();
	void handle_input();
	void move();
	void show_particles();
	void show();
};

#endif

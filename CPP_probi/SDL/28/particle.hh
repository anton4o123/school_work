#ifndef PARTICLE_HH__
#define PARTICLE_HH__

#include "../headers/basic.hh"

class Particle {
	int x, y, frame;
	SDL_Surface* type;
public:
	Particle(int X, int Y);
	void show();
	bool is_dead();
};

#endif

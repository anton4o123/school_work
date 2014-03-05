#ifndef FOO_HH__
#define FOO_HH__

#include "../headers/basic.hh"

class Foo {
	int offSet, offSet_up, velocity, velocity_up, frame, status;
public:
	Foo();
	void handle_events();
	void move();
	void show();
};

#endif

#ifndef WINDOW_HH__
#define WINDOW_HH__

#include "../headers/basic.hh"

class Window {
	bool windowed, windowOK;
public:
	Window();
	void handle_events();
	void toggle_fullscreen();
	bool error();
};

#endif

#ifndef STRING_INPUT_HH__
#define STRING_INPUT_HH__

#include "../headers/basic.hh"

class StringInput {
	std::string input;
	SDL_Surface* text;
public:
	StringInput();
	~StringInput();
	void handle_input();
	void show_centered();
};

#endif

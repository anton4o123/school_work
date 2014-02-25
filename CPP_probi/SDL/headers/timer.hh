#include "basic.hh"

class Timer {
	int startTicks, pausedTicks;
	bool paused, started;
public:
	Timer();
	void start();
	void stop();
	int get_ticks();
	void pause();
	void unpause();
	bool is_started();
	bool is_paused();
};

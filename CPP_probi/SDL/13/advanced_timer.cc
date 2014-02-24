#include "../headers/basic.hh"
#include <sstream>

class Timer {
	int startTicks, pausedTicks;
	bool paused, started;
public:
	Timer() {
		startTicks=0;
		pausedTicks=0;
		paused=false;
		started=false;
	}
	
	void start() {
		started=true;
		paused=false;
		startTicks=SDL_GetTicks();
	}
	
	void stop() {
		started=false;
		paused=false;
	}
	
	int get_ticks() {
		if(started==true) {
			if(paused==true) {
				return pausedTicks;
			} else {
				return SDL_GetTicks() - startTicks;
			}
		}
		return 0;
	}
	
	void pause() {
		if(started==true || paused==false) {
			paused=true;
			pausedTicks=SDL_GetTicks() - startTicks;
		}
	}
	
	void unpause() {
		if(paused==true) {
			paused=false;
			startTicks=SDL_GetTicks() - pausedTicks;
			pausedTicks=0;
		}
	}
	
	bool is_started() {
		return started;
	}
	
	bool is_paused() {
		return paused;
	}
};

SDL_Surface* screen=NULL;
SDL_Surface* background=NULL;
SDL_Surface* startStop=NULL;
SDL_Surface* pauseMessage=NULL;
SDL_Surface* seconds=NULL;
TTF_Font* font=NULL;
SDL_Event event;
SDL_Color textColor={0, 0, 0};

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1 || TTF_Init()==-1) {
		return false;
	}
	
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return false;
	}
	SDL_WM_SetCaption("Advaned timer", NULL);
	return true;
}

bool load_files() {
	background=load_image("background.png");
	font=TTF_OpenFont("lazy.ttf", 30);
	if(background==NULL || font==NULL) {
		return false;
	}
	return true;
}

void clean_up() {
	SDL_FreeSurface(background);
	SDL_FreeSurface(pauseMessage);
	SDL_FreeSurface(startStop);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	bool quit=false;
	
	if(init()==false || load_files()==false) {
		return 1;
	}
	
	Timer myTimer;
	
	startStop=TTF_RenderText_Solid(font, "Press S to start or stop the timer", textColor);
	pauseMessage=TTF_RenderText_Solid(font, "Press P to pause or unpause the timer", textColor);
	
	myTimer.start();
	
	while(quit==false) {
		while(SDL_PollEvent(&event)) {
			if(event.type==SDL_KEYDOWN) {
				if(event.key.keysym.sym==SDLK_s) {
					if(myTimer.is_started()==true) {
						myTimer.stop();
					} else {
						myTimer.start();
					}
				} else if(event.key.keysym.sym==SDLK_p) {
					if(myTimer.is_paused()==true) {
						myTimer.unpause();
					} else {
						myTimer.pause();
					}
				}
			} else if(event.type==SDL_QUIT) {
				quit=true;
			}
		}
		
		apply_surface(0, 0, background, screen, NULL);
		apply_surface((SCREEN_WIDTH-startStop->w)/2, 200, startStop, screen, NULL);
		apply_surface((SCREEN_WIDTH-pauseMessage->w)/2, 250, pauseMessage, screen, NULL);
		
		std::stringstream time;
		time << "Timer: " << myTimer.get_ticks() / 1000.f;
		seconds=TTF_RenderText_Solid(font, time.str().c_str(), textColor);
		apply_surface((SCREEN_WIDTH-seconds->w)/2, 0, seconds, screen, NULL);
		SDL_FreeSurface(seconds);
		if(SDL_Flip(screen)==-1) {
			return 1;
		}
	}
	
	clean_up();
	return 0;
}

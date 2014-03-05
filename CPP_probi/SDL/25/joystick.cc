#include "dot.hh"
#include "../headers/timer.hh"

const int DOT_WIDTH=20;
const int DOT_HEIGHT=20;
const int FRAMES_PER_SECOND=40;

SDL_Surface* screen=NULL;
SDL_Surface* dot=NULL;
SDL_Joystick* stick=NULL;
SDL_Event event;

Dot::Dot() {
	x=0;
	y=0;
	xVel=0;
	yVel=0;
}

void Dot::handle_input() {
	if(event.type==SDL_JOYAXISMOTION) {
		if(event.jaxis.which==0) {
			if(event.jaxis.axis==0) {
				if(event.jaxis.value>-8000 && event.jaxis.value<8000) {
					xVel=0;
				} else {
					if(event.jaxis.value<0) {
						xVel=-DOT_WIDTH;
					} else {
						xVel=DOT_WIDTH;
					}
				}
			} else if(event.jaxis.axis==1) {
				if(event.jaxis.value>-8000 && event.jaxis.value<8000) {
					yVel=0;
				} else {
					if(event.jaxis.value<0) {
						yVel=-DOT_HEIGHT;
					} else {
						yVel=DOT_HEIGHT;
					}
				}
			}
		}
	}
}

void Dot::move() {
	x+=xVel;
	if((x<0) || (x+DOT_WIDTH>SCREEN_WIDTH)) {
		x-=xVel;
	}
	
	y+=yVel;
	if((y<0) || (y+DOT_HEIGHT>SCREEN_HEIGHT)) {
		y-=yVel;
	}
}

void Dot::show() {
	apply_surface(x, y, dot, screen, NULL);
}

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1) {
		return false;
	}
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return false;
	}
	
	if(SDL_NumJoysticks()<1) {
		return false;
	}
	stick=SDL_JoystickOpen(0);
	if(stick==NULL) {
		return false;
	}
	
	SDL_WM_SetCaption("Move the dot", NULL);
	return true;
}

bool load_files() {
	dot=load_image("dot.bmp");
	if(dot==NULL) {
		return false;
	}
	return true;
}

void clean_up() {
	SDL_FreeSurface(dot);
	SDL_JoystickClose(stick);
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	bool quit=false;
	Timer fps;
	Dot myDot;
	
	if(!init() || !load_files()) {
		return 1;
	}
	
	while(!quit) {
		while(SDL_PollEvent(&event)) {
			myDot.handle_input();
			if(event.type==SDL_QUIT) {
				quit=true;
			}
		}
		myDot.move();
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
		myDot.show();
		
		if(SDL_Flip(screen)==-1) {
			return 1;
		}
		if(fps.get_ticks()<1000/FRAMES_PER_SECOND) {
			SDL_Delay((1000/FRAMES_PER_SECOND)-fps.get_ticks());
		}
	}
	
	clean_up();
	return 0;
}

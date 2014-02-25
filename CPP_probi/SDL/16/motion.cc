#include "../headers/basic.hh"
#include "../headers/timer.hh"
#include "dot.hh"

const int DOT_WIDTH=20;
const int DOT_HEIGHT=20;
const int FRAMES_PER_SECOND=20;

SDL_Surface* screen=NULL;
SDL_Surface* dot=NULL;
SDL_Event event;

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1) {
		return false;
	}
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return false;
	}
	SDL_WM_SetCaption("Moving dot", NULL);
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
	SDL_Quit();
}

Dot::Dot() {
	x=0;
	y=0;
	xVel=0;
	yVel=0;
}

void Dot::handle_input() {
	if(event.type==SDL_KEYDOWN) {
		switch(event.key.keysym.sym) {
			case SDLK_UP: yVel-=DOT_HEIGHT/2; break;
			case SDLK_DOWN: yVel+=DOT_HEIGHT/2; break;
			case SDLK_LEFT: xVel-=DOT_WIDTH/2; break;
			case SDLK_RIGHT: xVel+=DOT_WIDTH/2; break;
		}
	} else if(event.type==SDL_KEYUP) {
		switch (event.key.keysym.sym) {
			case SDLK_UP: yVel+=DOT_HEIGHT/2; break;
			case SDLK_DOWN: yVel-=DOT_HEIGHT/2; break;
			case SDLK_LEFT: xVel+=DOT_WIDTH/2; break;
			case SDLK_RIGHT: xVel-=DOT_WIDTH/2; break;
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

int main(int argc, char* argv[]) {
	bool quit=false;
	Dot myDot;
	Timer fps;
	
	if(init()==false || load_files()==false) {
		return 1;
	}
	
	while(quit==false) {
		fps.start();
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

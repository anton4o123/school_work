#include "dot.hh"
#include "../headers/timer.hh"

SDL_Surface* screen=NULL;
SDL_Surface* dot=NULL;
SDL_Event event;

Dot::Dot() {
	x=0;
	y=0;
	xVel=0;
	yVel=0;
}

void Dot::handle_input() {
	if(event.type==SDL_KEYDOWN) {
		switch(event.key.keysym.sym) {
			case SDLK_UP: yVel-=DOT_VEL;break;
			case SDLK_DOWN: yVel+=DOT_VEL;break;
			case SDLK_LEFT: xVel-=DOT_VEL;break;
			case SDLK_RIGHT: xVel+=DOT_VEL;break;
		}
	} else if(event.type==SDL_KEYUP) {
		switch(event.key.keysym.sym) {
			case SDLK_UP: yVel+=DOT_VEL;break;
			case SDLK_DOWN: yVel-=DOT_VEL;break;
			case SDLK_LEFT: xVel+=DOT_VEL;break;
			case SDLK_RIGHT: xVel-=DOT_VEL;break;
		}
	}
}

void Dot::move(Uint32 deltaTime) {
	x+=xVel*(deltaTime/1000.f);
	if(x<0) {
		x=0;
	} else if(x+DOT_WIDTH>SCREEN_WIDTH) {
		x=SCREEN_WIDTH-DOT_WIDTH;
	}
	
	y+=yVel*(deltaTime/1000.f);
	if(y<0) {
		y=0;
	} else if(y+DOT_HEIGHT>SCREEN_HEIGHT) {
		y=SCREEN_HEIGHT-DOT_HEIGHT;
	}
}

void Dot::show() {
	apply_surface((int)x, (int)y, dot, screen, NULL);
}

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1) {
		return false;
	}
	
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return false;
	}
	
	SDL_WM_SetCaption("Frame Independent Movement", NULL);
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

int main(int argc, char *argv[]) {
	bool quit=false;
	Dot myDot;
	Timer delta;
	
	if(!init() || !load_files()) {
		return 1;
	}
	
	delta.start();
	while(!quit) {
		while(SDL_PollEvent(&event)) {
			myDot.handle_input();
			if(event.type==SDL_QUIT) {
				quit=true;
			}
		}
		
		myDot.move(delta.get_ticks());
		delta.start();
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
		myDot.show();
		if(SDL_Flip(screen)==-1) {
			return 1;
		}
	}
	
	return 0;
}

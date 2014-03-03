#include "dot.hh"
#include "../headers/timer.hh"

const int FRAMES_PER_SECOND=20;
const int DOT_WIDTH=20;
const int DOT_HEIGHT=20;
const int LEVEL_WIDTH=1280;
const int LEVEL_HEIGHT=960;

SDL_Surface* screen=NULL;
SDL_Surface* background=NULL;
SDL_Surface* dot=NULL;
SDL_Event event;
SDL_Rect camera={0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

Dot::Dot() {
	x=0;
	y=0;
	xVel=0;
	yVel=0;
}

void Dot::handle_input() {
	if(event.type==SDL_KEYDOWN) {
		switch(event.key.keysym.sym) {
			case SDLK_UP: yVel-=DOT_HEIGHT/2;break;
			case SDLK_DOWN: yVel+=DOT_HEIGHT/2;break;
			case SDLK_LEFT: xVel-=DOT_WIDTH/2;break;
			case SDLK_RIGHT: xVel+=DOT_WIDTH/2;break;
		}
	} else if(event.type==SDL_KEYUP) {
		switch(event.key.keysym.sym) {
			case SDLK_UP: yVel+=DOT_HEIGHT/2;break;
			case SDLK_DOWN: yVel-=DOT_HEIGHT/2;break;
			case SDLK_LEFT: xVel+=DOT_WIDTH/2;break;
			case SDLK_RIGHT: xVel-=DOT_WIDTH/2;break;
		}
	}
}

void Dot::move() {
	x+=xVel;
	if(x<0 || x+DOT_WIDTH>LEVEL_WIDTH) {
		x-=xVel;
	}
	
	y+=yVel;
	if(y<0 || y+DOT_HEIGHT>LEVEL_HEIGHT) {
		y-=yVel;
	}
}

void Dot::set_camera() {
	camera.x=(x+DOT_WIDTH/2)-SCREEN_WIDTH/2;
	camera.y=(y+DOT_HEIGHT/2)-SCREEN_HEIGHT/2;
	
	if(camera.x<0) {
		camera.x=0;
	}
	if(camera.y<0) {
		camera.y=0;
	}
	if(camera.x>LEVEL_WIDTH-camera.w) {
		camera.x=LEVEL_WIDTH-camera.w;
	}
	if(camera.y>LEVEL_HEIGHT-camera.h) {
		camera.y=LEVEL_HEIGHT-camera.h;
	}
}

void Dot::show() {
	apply_surface(x-camera.x, y-camera.y, dot, screen, NULL);
}

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1) {
		return false;
	}
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return false;
	}
	SDL_WM_SetCaption("Chasing dot", NULL);
	return true;
}

bool load_files() {
	background=load_image("bg.png");
	dot=load_image("dot.bmp");
	if(background==NULL || dot==NULL) {
		return false;
	}
	return true;
}

void clean_up() {
	SDL_FreeSurface(background);
	SDL_FreeSurface(dot);
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	bool quit=false;
	Timer fps;
	Dot myDot;
	
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
		myDot.set_camera();
		apply_surface(0, 0, background, screen, &camera);
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

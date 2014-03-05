#include "dot.hh"
#include "../headers/timer.hh"

const int DOT_WIDTH=20;
const int DOT_HEIGHT=20;
const int FRAMES_PER_SECOND=20;

SDL_Surface* screen=NULL;
SDL_Surface* red=NULL;
SDL_Surface* green=NULL;
SDL_Surface* blue=NULL;
SDL_Surface* shimmer=NULL;
SDL_Surface* dot=NULL;
SDL_Event event;

Particle::Particle(int X, int Y) {
	x=X-5+(rand()%25);
	y=Y-5+(rand()%25);
	frame=rand()%5;
	switch(rand()%3) {
		case 0: type=red;break;
		case 1: type=green;break;
		case 2: type=blue;break;
	}
}

void Particle::show() {
	apply_surface(x, y, type, screen, NULL);
	if(frame%2) {
		apply_surface(x, y, shimmer, screen, NULL);
	}
	frame++;
}

bool Particle::is_dead() {
	if(frame>10) {
		return true;
	}
	return false;
}

Dot::Dot() {
	x=0;
	y=0;
	xVel=0;
	yVel=0;
	for(int p=0;p<TOTAL_PARTICLES;++p) {
		particles[p]=new Particle(x, y);
	}
}

Dot::~Dot() {
	for(int p=0;p<TOTAL_PARTICLES;++p) {
		delete particles[p];
	}
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
	show_particles();
}

void Dot::show_particles() {
	for(int p=0;p<TOTAL_PARTICLES;p++) {
		if(particles[p]->is_dead()) {
			delete particles[p];
			particles[p]=new Particle(x, y);
		}
	}
	
	for(int p=0;p<TOTAL_PARTICLES;p++) {
		particles[p]->show();
	}
}

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1) {
		return false;
	}
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return false;
	}
	SDL_WM_SetCaption("Particles", NULL);
	srand(SDL_GetTicks());
	return true;
}

bool load_files() {
	dot=load_image("dot.bmp");
	red=load_image("red.bmp");
	green=load_image("green.bmp");
	blue=load_image("blue.bmp");
	shimmer=load_image("shimmer.bmp");
	if(dot==NULL || red==NULL || green==NULL || blue==NULL || shimmer==NULL) {
		return false;
	}
	return true;
}

void clean_up() {
	SDL_FreeSurface(dot);
	SDL_FreeSurface(red);
	SDL_FreeSurface(green);
	SDL_FreeSurface(blue);
	SDL_FreeSurface(shimmer);
	SDL_Quit();
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

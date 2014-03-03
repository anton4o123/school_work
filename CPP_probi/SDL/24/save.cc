#include "dot.hh"
#include "../headers/timer.hh"
#include <fstream>

const int DOT_WIDTH=20;
const int DOT_HEIGHT=20;
const int FRAMES_PER_SECOND=20;

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
			case SDLK_UP: yVel-=DOT_HEIGHT/4;break;
			case SDLK_DOWN: yVel+=DOT_HEIGHT/4;break;
			case SDLK_LEFT: xVel-=DOT_WIDTH/4;break;
			case SDLK_RIGHT: xVel+=DOT_WIDTH/4;break;
		}
	} else if(event.type==SDL_KEYUP) {
		switch(event.key.keysym.sym) {
			case SDLK_UP: yVel+=DOT_HEIGHT/4;break;
			case SDLK_DOWN: yVel-=DOT_HEIGHT/4;break;
			case SDLK_LEFT: xVel+=DOT_WIDTH/4;break;
			case SDLK_RIGHT: xVel-=DOT_WIDTH/4;break;
		}
	}
}

void Dot::move() {
	x+=xVel;
	if(x<0 || x+DOT_WIDTH>SCREEN_WIDTH) {
		x-=xVel;
	}
	
	y+=yVel;
	if(y<0 || y+DOT_HEIGHT>SCREEN_HEIGHT) {
		y-=yVel;
	}
}

void Dot::show() {
	apply_surface(x, y, dot, screen, NULL);
}

int Dot::get_x() {
	return x;
}

int Dot::get_y() {
	return y;
}

void Dot::set_x(int X) {
	x=X;
}

void Dot::set_y(int Y) {
	y=Y;
}

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1) {
		return false;
	}
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return false;
	}
	SDL_WM_SetCaption("Cool game", NULL);
	return true;
}

bool load_files(Dot &thisDot, Uint32 &bg) {
	dot=load_image("dot.bmp");
	if(dot==NULL) {
		return false;
	}
	std::ifstream load("game_save");
	if(load!=NULL) {
		int offset;
		std::string level;
		
		load >> offset;
		thisDot.set_x(offset);
		load >> offset;
		thisDot.set_y(offset);
		
		if(thisDot.get_x()<0 || thisDot.get_x()>SCREEN_WIDTH-DOT_WIDTH) {
			return false;
		}
		if(thisDot.get_y()<0 || thisDot.get_y()>SCREEN_HEIGHT-DOT_HEIGHT) {
			return false;
		}
		load.ignore();
		getline(load, level);
		
		if(load.fail()) {
			return false;
		}
		
		if(level=="White level") {
			bg=SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);
		} else if(level=="Red level") {
			bg=SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
		} else if(level=="Green level") {
			bg=SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
		} else if(level=="Blue level") {
			bg=SDL_MapRGB(screen->format, 0x00, 0x00, 0xFF);
		}
		load.close();
	}
	return true;
}

void clean_up(Dot &thisDot, Uint32 &bg) {
	SDL_FreeSurface(dot);
	std::ofstream save("game_save");
	save << thisDot.get_x();
	save << " ";
	save << thisDot.get_y();
	save << "\n";
	
	Uint8 r, g, b;
	SDL_GetRGB(bg, screen->format, &r, &g, &b);
	if((r==0xFF) && (g==0xFF) && (b==0xFF)) {
		save << "White level";
	} else if(r==0xFF) {
		save << "Red level";
	} else if(g==0xFF) {
		save << "Green level";
	} else if(b==0xFF) {
		save << "Blue level";
	}
	save.close();
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	bool quit=false;
	Dot myDot;
	Timer fps;
	
	if(init()==false) {
		return 1;
	}
	
	Uint32 background=SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);

	if(load_files(myDot, background)==false) {
		return 1;
	}
	
	while(quit==false) {
		fps.start();
		while(SDL_PollEvent(&event)) {
			myDot.handle_input();
			if(event.type==SDL_KEYDOWN) {
				switch(event.key.keysym.sym) {
					case SDLK_1: background=SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);break;
					case SDLK_2: background=SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);break;
					case SDLK_3: background=SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);break;
					case SDLK_4: background=SDL_MapRGB(screen->format, 0x00, 0x00, 0xFF);break;
				}
			}
			if(event.type==SDL_QUIT) {
				quit=true;
			}
		}
		
		myDot.move();
		SDL_FillRect(screen, &screen->clip_rect, background);
		myDot.show();
		if(SDL_Flip(screen)==-1) {
			return 1;
		}
		if(fps.get_ticks()<1000/FRAMES_PER_SECOND) {
			SDL_Delay((1000/FRAMES_PER_SECOND)-fps.get_ticks());
		}
	}
	
	clean_up(myDot, background);
	return 0;
}

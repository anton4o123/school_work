#include "dot.hh"
#include "../headers/timer.hh"

const int DOT_WIDTH=20;
const int FRAMES_PER_SECOND=60;
const int SPEED=20;

SDL_Surface* screen=NULL;
SDL_Surface* dot=NULL;
SDL_Event event;

double distance(int x1, int y1, int x2, int y2) {
	return sqrt(pow(x2-x1, 2)+pow(y2-y1, 2));
}

bool check_collision(Circle &A, Circle &B) {
	if(distance(A.x, A.y, B.x, B.y)<(A.r+B.r)) {
		return true;
	}
	return false;
}

bool check_collision(Circle &A, std::vector<SDL_Rect> &B) {
	int cX, cY;
	
	for(int Bbox=0; Bbox<B.size(); ++Bbox) {
		if(A.x<B[Bbox].x) {
			cX=B[Bbox].x;
		} else if(A.x>B[Bbox].x+B[Bbox].w) {
			cX=B[Bbox].x+B[Bbox].w;
		} else {
			cX=A.x;
		}
		
		if(A.y<B[Bbox].y) {
			cY=B[Bbox].y;
		} else if(A.y>B[Bbox].y+B[Bbox].h) {
			cY=B[Bbox].y+B[Bbox].h;
		} else {
			cY=A.y;
		}
		
		if(distance(A.x, A.y, cX, cY)<A.r) {
			return true;
		}
	}
	return false;
}

Dot::Dot() {
	c.x=DOT_WIDTH/2;
	c.y=DOT_WIDTH/2;
	c.r=DOT_WIDTH/2;
	xVel=0;
	yVel=0;
}

void Dot::handle_input() {
	if(event.type==SDL_KEYDOWN) {
		switch(event.key.keysym.sym) {
			case SDLK_UP: yVel-=SPEED;break;
			case SDLK_DOWN: yVel+=SPEED;break;
			case SDLK_LEFT: xVel-=SPEED;break;
			case SDLK_RIGHT: xVel+=SPEED;break;
		}
	} else if(event.type==SDL_KEYUP) {
		switch(event.key.keysym.sym) {
			case SDLK_UP: yVel+=SPEED;break;
			case SDLK_DOWN: yVel-=SPEED;break;
			case SDLK_LEFT: xVel+=SPEED;break;
			case SDLK_RIGHT: xVel-=SPEED;break;
		}
	}
}

void Dot::move(std::vector<SDL_Rect> &rects, Circle &circle) {
	c.x += xVel;

	if(c.x-DOT_WIDTH/2<0 || c.x+DOT_WIDTH/2>SCREEN_WIDTH || check_collision(c, rects) || check_collision(c, circle)) {
		c.x -= xVel;
	}

	c.y += yVel;

	if(c.y-DOT_WIDTH/2<0 || c.y+DOT_WIDTH/2>SCREEN_HEIGHT || check_collision(c, rects ) || check_collision(c, circle)) {
		c.y -= yVel;
	}
}

void Dot::show() {
	apply_surface(c.x-c.r, c.y-c.r, dot, screen, NULL);
}

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1) {
		return false;
	}
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return false;
	}
	SDL_WM_SetCaption("Simulator", NULL);
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

int main(int argc, char* argv[]) {
	bool quit=false;
	Timer fps;
	std::vector<SDL_Rect> box(1);
	Circle otherDot;
	Dot myDot;
	
	if(init()==false || load_files()==false) {
		return 1;
	}
	
	box[0].x=60;
	box[0].y=60;
	box[0].w=40;
	box[0].h=40;
	
	otherDot.x=30;
	otherDot.y=30;
	otherDot.r=DOT_WIDTH/2;
	
	while(quit==false) {
		fps.start();
		while(SDL_PollEvent(&event)) {
			myDot.handle_input();
			if(event.type==SDL_QUIT) {
				quit=true;
			}
		}
		myDot.move(box, otherDot);
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF,0xFF,0xFF));
		SDL_FillRect(screen, &box[0], SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
		apply_surface(otherDot.x-otherDot.r, otherDot.y-otherDot.r, dot, screen, NULL);
		myDot.show();
		if(SDL_Flip(screen)==-1) {
			return 1;
		}
		if(fps.get_ticks()<1000/FRAMES_PER_SECOND) {
			SDL_Delay((1000/FRAMES_PER_SECOND)-fps.get_ticks());
		}
	}
	
	return 0;
}

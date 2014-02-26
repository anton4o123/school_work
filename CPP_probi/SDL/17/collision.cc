#include "../headers/basic.hh"
#include "../headers/timer.hh"
#include "square.hh"

SDL_Surface* screen=NULL;
SDL_Surface* square=NULL;
SDL_Event event;

const int SQUARE_WIDTH=20;
const int SQUARE_HEIGHT=20;
const int FRAMES_PER_SECOND=20;

SDL_Rect wall;

bool check_collision(SDL_Rect A, SDL_Rect B) {
	int leftA, leftB, rightA, rightB, topA, topB, bottomA, bottomB;
	
	leftA=A.x;
	rightA=A.x+A.w;
	topA=A.y;
	bottomA=A.y+A.h;
	leftB=B.x;
	rightB=B.x+B.w;
	topB=B.y;
	bottomB=B.y+B.h;
	
	if(bottomA<=topB) {
		return false;
	}
	
	if(topA>=bottomB) {
		return false;
	}
	
	if(rightA<=leftB) {
		return false;
	}
	
	if(leftA>=rightB) {
		return false;
	}
	return true;
}

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1) {
		return false;
	}
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return false;
	}
	SDL_WM_SetCaption("Collision", NULL);
	return true;
}

bool load_files() {
	square=load_image("square.bmp");
	if(square==NULL) {
		return false;
	}
	return true;
}

void clean_up() {
	SDL_FreeSurface(square);
	SDL_Quit();
}

Square::Square() {
	box.x=0;
	box.y=0;
	box.w=SQUARE_WIDTH;
	box.h=SQUARE_HEIGHT;
	xVel=0;
	yVel=0;
}

void Square::handle_input() {
	if(event.type==SDL_KEYDOWN) {
		switch(event.key.keysym.sym) {
			case SDLK_UP: yVel-=SQUARE_HEIGHT/2; break;
			case SDLK_DOWN: yVel+=SQUARE_HEIGHT/2; break;
			case SDLK_LEFT: xVel-=SQUARE_WIDTH/2; break;
			case SDLK_RIGHT: xVel+=SQUARE_WIDTH/2; break;
		}
	} else if(event.type==SDL_KEYUP) {
			switch(event.key.keysym.sym) {
			case SDLK_UP: yVel+=SQUARE_HEIGHT/2; break;
			case SDLK_DOWN: yVel-=SQUARE_HEIGHT/2; break;
			case SDLK_LEFT: xVel+=SQUARE_WIDTH/2; break;
			case SDLK_RIGHT: xVel-=SQUARE_WIDTH/2; break;
		}
	}
}

void Square::move() {
	box.x+=xVel;
	if((box.x<0) || (box.x+SQUARE_WIDTH>SCREEN_WIDTH) || (check_collision(box, wall))) {
		box.x-=xVel;
	}
	
	box.y+=yVel;
	if((box.y<0) || (box.y+SQUARE_HEIGHT>SCREEN_HEIGHT) || (check_collision(box, wall))) {
		box.y-=yVel;
	}
}

void Square::show() {
	apply_surface(box.x, box.y, square, screen, NULL);
}

int main(int argc, char* argv[]) {
	bool quit=false;
	Timer fps;
	Square mySquare;
	
	wall.x=300;
	wall.y=40;
	wall.w=40;
	wall.h=400;
	if(init()==false || load_files()==false) {
		return 1;
	}
	
	while(quit==false) {
		fps.start();
		while(SDL_PollEvent(&event)) {
			mySquare.handle_input();
			if(event.type==SDL_QUIT) {
				quit=true;
			}
		}
		mySquare.move();
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
		SDL_FillRect(screen, &wall, SDL_MapRGB(screen->format, 0x77, 0x77, 0x77));
		mySquare.show();
		
		if(SDL_Flip(screen)==-1) {
			return 1;
		}
		
		if(fps.get_ticks()<500/FRAMES_PER_SECOND) {
			SDL_Delay((500/FRAMES_PER_SECOND)-fps.get_ticks());
		}
	}
	
	clean_up();
	return 0;
}

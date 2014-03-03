#include "dot.hh"
#include "../headers/timer.hh"

const int DOT_WIDTH=20;
const int DOT_HEIGHT=20;
const int FRAMES_PER_SECOND=20;

SDL_Surface* screen=NULL;
SDL_Surface* dot=NULL;
SDL_Event event;

bool check_collision(std::vector<SDL_Rect> &A, std::vector<SDL_Rect> &B) {
	int leftA, leftB, rightA, rightB, bottomA, bottomB, topA, topB;
	
	for(int Abox=0; Abox<A.size(); ++Abox) {
		leftA=A[Abox].x;
		rightA=A[Abox].x+A[Abox].w;
		topA=A[Abox].y;
		bottomA=A[Abox].y+A[Abox].h;
		
		for(int Bbox=0; Bbox<B.size(); ++Bbox) {
			leftB=B[Bbox].x;
			rightB=B[Bbox].x+B[Bbox].w;
			topB=B[Bbox].y;
			bottomB=B[Bbox].y+B[Bbox].h;
			
			if(!(bottomA<=topB || topA>=bottomB || rightA<=leftB || leftA>=rightB)) {
				return true;
			}
		}
	}
	return false;
}

Dot::Dot(int X, int Y) {
	x=X;
	y=Y;
	xVel=0;
	yVel=0;
	
	box.resize(11);
	
	box[0].w=6;
	box[0].h=1;
	
	box[1].w=10;
	box[1].h=1;
	
	box[2].w=14;
	box[2].h=1;
	
	box[3].w=16;
	box[3].h=2;
	
	box[4].w=18;
	box[4].h=2;
	
	box[5].w=20;
	box[5].h=6;
	
	box[6].w=18;
	box[6].h=2;
	
	box[7].w=16;
	box[7].h=2;
	
	box[8].w=14;
	box[8].h=1;
	
	box[9].w=10;
	box[9].h=1;
	
	box[10].w=6;
	box[10].h=1;
	
	shift_boxes();
}

void Dot::shift_boxes() {
	int r=0;
	
	for(int set=0; set<box.size(); ++set) {
		box[set].x=x+(DOT_WIDTH-box[set].w)/2;
		box[set].y=y+r;
		r+=box[set].h;
	}
}

void Dot::handle_input() {
	if(event.type==SDL_KEYDOWN) {
		switch(event.key.keysym.sym) {
			case SDLK_UP: yVel-=1;break;
			case SDLK_DOWN: yVel+=1;break;
			case SDLK_LEFT: xVel-=1;break;
			case SDLK_RIGHT: xVel+=1;break;
		}
	} else if(event.type==SDL_KEYUP) {
		switch(event.key.keysym.sym) {
			case SDLK_UP: yVel+=1;break;
			case SDLK_DOWN: yVel-=1;break;
			case SDLK_LEFT: xVel+=1;break;
			case SDLK_RIGHT: xVel-=1;break;
		}
	}
}

void Dot::move(std::vector<SDL_Rect> &rects) {
	x+=xVel;
	shift_boxes();
	
	if(x<0 || x+DOT_WIDTH>SCREEN_WIDTH || check_collision(box, rects)) {
		x-=xVel;
		shift_boxes();
	}
	
	y+=yVel;
	shift_boxes();
	
	if(y<0 || y+DOT_HEIGHT>SCREEN_HEIGHT || check_collision(box, rects)) {
		y-=yVel;
		shift_boxes();
	}
}

void Dot::show() {
	apply_surface(x, y, dot, screen, NULL);
}

std::vector<SDL_Rect> &Dot::get_rects() {
	return box;
}

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

int main(int argc, char* argv[]) {
	Dot myDot(0, 0), otherDot(20, 20);
	bool quit=false;
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
		myDot.move(otherDot.get_rects());
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
		
		otherDot.show();
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

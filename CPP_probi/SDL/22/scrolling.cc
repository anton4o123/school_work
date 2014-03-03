#include "../headers/basic.hh"
#include "../headers/timer.hh"

const int FRAMES_PER_SECOND=20;

SDL_Surface* screen=NULL;
SDL_Surface* background=NULL;
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
	SDL_WM_SetCaption("Moving screen", NULL);
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
	int bgX=0, bgY=0;
	bool quit=false;
	Timer fps;
	
	if(init()==false || load_files()==false) {
		return 1;
	}
	
	while(quit==false) {
		fps.start();
		while(SDL_PollEvent(&event)) {
			if(event.type==SDL_QUIT) {
				quit=true;
			}
		}
		bgX-=2;
		if(bgX<=-background->w) {
			bgX=0;
		}
		apply_surface(bgX, bgY, background, screen, NULL);
		apply_surface(bgX+background->w, bgY, background, screen, NULL);
		apply_surface(310, 230, dot, screen, NULL);
		if(SDL_Flip(screen)==-1) {
			return 1;
		}
		if(fps.get_ticks()-1000/FRAMES_PER_SECOND) {
			SDL_Delay((1000/FRAMES_PER_SECOND)-fps.get_ticks());
		}
	}
	
	clean_up();
	return 0;
}

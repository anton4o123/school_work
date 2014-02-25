#include "../headers/basic.hh"
#include "../headers/timer.hh"
#include <sstream>

SDL_Surface* screen=NULL;
SDL_Surface* image=NULL;
SDL_Event event;

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1) {
		return false;
	}
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return false;
	}
	SDL_WM_SetCaption("Frame rate test", NULL);
	return true;
}

bool load_files() {
	image=load_image("testing.png");
	if(image==NULL) {
		return false;
	}
	return true;
}

void clean_up() {
	SDL_FreeSurface(image);
	SDL_Quit();
}

int main() {
	bool quit=false;
	int frame=0;
	Timer fps, update;
	
	if(init()==false || load_files()==false) {
		return 1;
	}
	
	update.start();
	fps.start();
	
	while(quit==false) {
		while(SDL_PollEvent(&event)) {
			if(event.type==SDL_QUIT) {
				quit=true;
			}
		}
		apply_surface(0, 0, image, screen, NULL);
		if(SDL_Flip(screen)==-1) {
			return 1;
		}
		frame++;
		
		if(update.get_ticks()>1000) {
			std::stringstream caption;
			caption << "Average Frames Per Second: " << frame/(fps.get_ticks()/1000.f);
			SDL_WM_SetCaption(caption.str().c_str(), NULL);
			update.start();
		}
	}

	return 0;
}

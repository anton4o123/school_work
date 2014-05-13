#include "../headers/basic.hh"
#include <iostream>

SDL_Surface* screen=NULL;
SDL_Event event;

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1) {
		return false;
	}
	
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return false;
	}
	
	SDL_WM_SetCaption("Proba", NULL);
	return true;
}

void clean_up() {
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	bool change=false;
	
	if(!init()) {
		return 1;
	}
	
	while(true) {
		if(SDL_PollEvent(&event)) {
			if(event.type==SDL_QUIT) {
				break;
			}
			
			if(event.type==SDL_MOUSEMOTION) {
				if((event.motion.x>540) && (event.motion.y>380)) {
					if(!change) {
						SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00));
						SDL_Flip(screen);
						change=true;
					}
				} else if(change) {
					SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0xFF));
					SDL_Flip(screen);
					change=false;
				}
			}
		}
	}
	
	return 0;
}

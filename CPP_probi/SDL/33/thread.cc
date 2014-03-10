#include "../headers/basic.hh"
#include "SDL/SDL_thread.h"

bool quit=false;
SDL_Thread *thread=NULL;

SDL_Surface *screen=NULL;
SDL_Surface *image=NULL;
SDL_Event event;

int my_thread(void *data) {
	while(!quit) {
		SDL_WM_SetCaption("Thread is running", NULL);
		SDL_Delay(250);
		SDL_WM_SetCaption("Thread is running.", NULL);
		SDL_Delay(250);
		SDL_WM_SetCaption("Thread is running..", NULL);
		SDL_Delay(250);
		SDL_WM_SetCaption("Thread is running...", NULL);
		SDL_Delay(250);
	}
	return 0;
}

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1) {
		return false;
	}
	
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return false;
	}
	return true;
}

bool load_files() {
	image=load_image("image.png");
	if(image==NULL) {
		return false;
	}
	return true;
}

void clean_up() {
	SDL_KillThread(thread);
	SDL_FreeSurface(image);
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	if(!init() || !load_files()) {
		return false;
	}
	
	thread=SDL_CreateThread(my_thread, NULL);
	apply_surface(0, 0, image, screen, NULL);
	if(SDL_Flip(screen)==-1) {
		return false;
	}
	
	while(!quit) {
		while(SDL_PollEvent(&event)) {
			if(event.type==SDL_QUIT) {
				quit=true;
			}
		}
	}

	clean_up();
	return 0;
}

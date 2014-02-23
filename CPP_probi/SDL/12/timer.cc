#include "../headers/basic.hh"
#include <sstream>

SDL_Surface* screen=NULL;
SDL_Surface* background=NULL;
SDL_Surface* seconds=NULL;
SDL_Surface* startStop=NULL;
TTF_Font* font=NULL;
SDL_Event event;
SDL_Color textColor={0, 0, 0};

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1 || TTF_Init()==-1) {
		return false;
	}
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return false;
	}
	SDL_WM_SetCaption("Timer", NULL);
	return true;
}

bool load_files() {
	background=load_image("background.png");
	font=TTF_OpenFont("lazy.ttf", 30);
	if(background==NULL || font==NULL) {
		return false;
	}
	return true;
}

void clean_up() {
	SDL_FreeSurface(background);
	SDL_FreeSurface(startStop);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	bool quit=false, running=true;
	Uint32 start=0;
	start=SDL_GetTicks();
	
	if(init()==false || load_files()==false) {
		return 1;
	}
	startStop=TTF_RenderText_Solid(font, "Press S to start or stop the timer", textColor);
	
	while(quit==false) {
		while(SDL_PollEvent(&event)) {
			if(event.type==SDL_KEYDOWN) {
				if(event.key.keysym.sym==SDLK_s) {
					if(running==true) {
						running=false;
						start=0;
					} else {
						running=true;
						start=SDL_GetTicks();
					}
				}
			} else if(event.type==SDL_QUIT) {
				quit=true;
			}
		}
		
		apply_surface(0, 0, background, screen, NULL);
		apply_surface((SCREEN_WIDTH-screen->w)/2, 200, startStop, screen, NULL);
		
		if(running==true) {
			std::stringstream time;
			time << "Timer: " << SDL_GetTicks()-start;
			seconds=TTF_RenderText_Solid(font, time.str().c_str(), textColor);
			apply_surface((SCREEN_WIDTH-screen->w)/2, 50, seconds, screen, NULL);
			SDL_FreeSurface(seconds);
		}
		
		if(SDL_Flip(screen)==-1) {
			return 1;
		}
	}

	return 0;
}

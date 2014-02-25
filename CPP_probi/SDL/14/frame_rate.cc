#include "../headers/basic.hh"
#include "../headers/timer.hh"

const int FRAMES_PER_SECOND=20;

SDL_Surface* screen=NULL;
SDL_Surface* background=NULL;
SDL_Surface* message=NULL;
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
	SDL_WM_SetCaption("Frame rating", NULL);
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
	SDL_FreeSurface(message);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	bool quit=false, cap=true;
	int frame=0;
	Timer fps;
	
	if(init()==false || load_files()==false) {
		return 1;
	}
	
	message=TTF_RenderText_Solid(font, "Testing frame rate", textColor);
	
	while(quit==false) {
		fps.start();
		while(SDL_PollEvent(&event)) {
			if(event.type==SDL_KEYDOWN) {
				if(event.key.keysym.sym==SDLK_RETURN) {
					cap=(!cap);
				}
			} else if(event.type==SDL_QUIT) {
				quit=true;
			}
		}
		apply_surface(0, 0, background, screen, NULL);
		apply_surface((SCREEN_WIDTH-message->w)/2, ((SCREEN_HEIGHT+message->h*2)/FRAMES_PER_SECOND)*(frame%FRAMES_PER_SECOND)-message->h, message, screen, NULL);
		
		if(SDL_Flip(screen)==-1) {
			return 1;
		}
		frame++;
		if((cap==true) && (fps.get_ticks()<1000/FRAMES_PER_SECOND)) {
			SDL_Delay((1000/FRAMES_PER_SECOND)-fps.get_ticks());
		}
	}
	
	clean_up();
	return 0;	
}

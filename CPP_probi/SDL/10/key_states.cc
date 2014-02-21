#include "basic.hh"

SDL_Surface* background=NULL;
SDL_Surface* up=NULL;
SDL_Surface* down=NULL;
SDL_Surface* left=NULL;
SDL_Surface* right=NULL;
TTF_Font* font=NULL;
SDL_Surface* screen=NULL;

SDL_Event event;
SDL_Color textColor={0, 0, 0};

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1) {
		return false;
	}
	
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return false;
	}
	
	if(TTF_Init()==-1) {
		return false;
	}
	
	SDL_WM_SetCaption("Key states", NULL);
	return true;
}

bool load_files() {
	background=load_image("background.png");
	font=TTF_OpenFont("lazy.ttf", 72);
	if(background==NULL || font==NULL) {
		return false;
	}
	return true;
}

void clean_up() {
	SDL_FreeSurface(background);
	SDL_FreeSurface(up);
	SDL_FreeSurface(down);
	SDL_FreeSurface(left);
	SDL_FreeSurface(right);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	bool quit=false;
	
	if(init()==false || load_files()==false) {
		return 1;
	}
	
	up=TTF_RenderText_Solid(font, "Up", textColor);
	down=TTF_RenderText_Solid(font, "Down", textColor);
	left=TTF_RenderText_Solid(font, "Left", textColor);
	right=TTF_RenderText_Solid(font, "Right", textColor);

	while(quit==false) {
		while(SDL_PollEvent(&event)) {
			if(event.type==SDL_QUIT) {
				quit=true;
			}
		}
		
		apply_surface(0, 0, background, screen, NULL);
		Uint8* keystates=SDL_GetKeyState(NULL);
		if(keystates[SDLK_UP]) {
			apply_surface((SCREEN_WIDTH-up->w)/2, (SCREEN_HEIGHT/2-up->h)/2, up, screen, NULL);
		}
		if(keystates[SDLK_DOWN]) {
			apply_surface((SCREEN_WIDTH-down->w)/2, (SCREEN_HEIGHT/2-down->h)/2+(SCREEN_HEIGHT/2), down, screen, NULL);
		}
		if(keystates[SDLK_LEFT]) {
			apply_surface((SCREEN_WIDTH/2-left->w)/2, (SCREEN_HEIGHT-left->h)/2, left, screen, NULL);
		}
		if(keystates[SDLK_RIGHT]) {
			apply_surface((SCREEN_WIDTH/2-right->w)/2+(SCREEN_WIDTH/2), (SCREEN_HEIGHT-right->h)/2, right, screen, NULL);
		}
		
		if(SDL_Flip(screen)==-1) {
			return 1;
		}
	}

	clean_up();
	return 0;
}

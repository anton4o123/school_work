#include "window.hh"

SDL_Surface* screen=NULL;
SDL_Surface* testing=NULL;
SDL_Event event;

Window::Window() {
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE);
	if(screen==NULL) {
		windowOK=false;
		return;
	} else {
		windowOK=true;
	}
	
	SDL_WM_SetCaption("Window Event Test", NULL);
	windowed=true;
}

void Window::toggle_fullscreen() {
	if(windowed) {
		screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE | SDL_FULLSCREEN);
		if(screen==NULL) {
			windowOK=false;
			return;
		}
		windowed=false;
	} else {
		screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE);
		if(screen==NULL) {
			windowOK=false;
			return;
		}
		windowed=true;
	}
}

void Window::handle_events() {
	if(!windowOK) {
		return;
	}
	
	if(event.type==SDL_VIDEORESIZE) {
		screen=SDL_SetVideoMode(event.resize.w, event.resize.h, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE);
		if(screen==NULL) {
			windowOK=false;
			return;
		}
	} else if((event.type==SDL_KEYDOWN) && (event.key.keysym.sym==SDLK_RETURN)) {
		toggle_fullscreen();
	} else if(event.type==SDL_ACTIVEEVENT) {
		if(event.active.state & SDL_APPACTIVE) {
			if(event.active.gain==0) {
				SDL_WM_SetCaption("Window Event Test: Iconified", NULL);
			} else {
				SDL_WM_SetCaption("Window Event Test", NULL);
			}
		} else if(event.active.state & SDL_APPINPUTFOCUS) {
			if(event.active.gain==0) {
				SDL_WM_SetCaption("Window Event Test: Keyboard Fosuc lost", NULL);
			} else {
				SDL_WM_SetCaption("Window Event Test", NULL);
			}
		} else if(event.active.state & SDL_APPMOUSEFOCUS) {
			if(event.active.gain==0) {
				SDL_WM_SetCaption("Window Event Test: Mouse Focus lost", NULL);
			} else {
				SDL_WM_SetCaption("Window Event Test", NULL);
			}
		}
	} else if(event.type==SDL_VIDEOEXPOSE) {
		if(SDL_Flip(screen)==-1) {
			windowOK=false;
			return;
		}
	}
}

bool Window::error() {
	return !windowOK;
}

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1) {
		return false;
	}
	return true;
}

bool load_files() {
	testing=load_image("window.png");
	if(testing==NULL) {
		return false;
	}
	return true;
}

void clean_up() {
	SDL_FreeSurface(testing);
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	bool quit=false;
	Window myWindow;
	
	if(!init() || !load_files()) {
		return 1;
	}
	
	if(myWindow.error()) {
		return 1;
	}
	
	while(quit==false) {
		while(SDL_PollEvent(&event)) {
			myWindow.handle_events();
			if((event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_ESCAPE) || event.type==SDL_QUIT) {
				quit=true;
			}
		}
		
		if(myWindow.error()) {
			return 1;
		}
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
		apply_surface((screen->w-testing->w)/2, (screen->h-testing->h)/2, testing, screen, NULL);
		if(SDL_Flip(screen)==-1) {
			return 1;
		}
	}
	
	clean_up();
	return 0;
}

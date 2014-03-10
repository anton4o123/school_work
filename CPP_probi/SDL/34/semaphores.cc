#include "../headers/basic.hh"
#include "SDL/SDL_thread.h"

SDL_Thread *threadA=NULL;
SDL_Thread *threadB=NULL;
SDL_sem *videoLock=NULL;

SDL_Surface *screen=NULL;
SDL_Surface *background=NULL;
SDL_Surface *text[5]={NULL, NULL, NULL, NULL, NULL};
SDL_Event event;

SDL_Color textColor={0, 0, 0};

TTF_Font *font=NULL;

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1 || TTF_Init()==-1) {
		return false;
	}
	
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return false;
	}
	
	videoLock=SDL_CreateSemaphore(1);
	SDL_WM_SetCaption("Testing threads", NULL);
	return true;
}

bool load_files() {
	background=load_image("background.png");
	font=TTF_OpenFont("lazy.ttf", 72);
	if(background==NULL || font==NULL) {
		return false;
	}
	
	text[0]=TTF_RenderText_Solid(font, "One", textColor);
	text[1]=TTF_RenderText_Solid(font, "Two", textColor);
	text[2]=TTF_RenderText_Solid(font, "Three", textColor);
	text[3]=TTF_RenderText_Solid(font, "Four", textColor);
	text[4]=TTF_RenderText_Solid(font, "Five", textColor);
	
	return true;
}

void clean_up() {
	SDL_DestroySemaphore(videoLock);
	SDL_FreeSurface(background);
	for(int t=0;t<5;++t) {
		SDL_FreeSurface(text[t]);
	}
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}

void show_surface(int x, int y, SDL_Surface *source) {
	SDL_SemWait(videoLock);
	
	SDL_Rect offset;
	
	offset.x=x;
	offset.y=y;
	
	SDL_BlitSurface(source, NULL, screen, &offset);
	SDL_Flip(screen);
	
	SDL_SemPost(videoLock);
}

int blitter_a(void *data) {
	int y=10;
	
	for(int b=0;b<5;++b) {
		SDL_Delay(1000);
		show_surface(((SCREEN_WIDTH/2)-text[b]->w)/2, y, text[b]);
		y+=100;
	}
	
	return 0;
}

int blitter_b(void *data) {
	int y=10;
	
	for(int b=0;b<5;++b) {
		SDL_Delay(1000);
		show_surface((SCREEN_WIDTH/2)+(((SCREEN_WIDTH/2)-text[b]->w)/2), y, text[b]);
		y+=100;
	}
	
	return 0;
}

int main(int argc, char *argv[]) {
	bool quit=false;
	
	if(!init() || !load_files()) {
		return 1;
	}
	
	show_surface(0, 0, background);
	
	threadA=SDL_CreateThread(blitter_a, NULL);
	threadB=SDL_CreateThread(blitter_b, NULL);
	
	SDL_WaitThread(threadA, NULL);
	SDL_WaitThread(threadB, NULL);
	
	while(!quit) {
		while(SDL_PollEvent(&event)) {
			if(event.type==SDL_QUIT) {
				quit==true;
			}
		}
	}

	clean_up();
	return 0;
}

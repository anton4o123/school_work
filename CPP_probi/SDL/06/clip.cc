#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
const int SCREEN_BPP=32;

SDL_Surface* dots=NULL;
SDL_Surface* screen=NULL;
SDL_Event event;
SDL_Rect clip[4];

SDL_Surface* load_image(std::string filename) {
	SDL_Surface* loadedImage=NULL;
	SDL_Surface* optimizedImage=NULL;
	
	loadedImage=IMG_Load(filename.c_str());
	if(loadedImage!=NULL) {
		optimizedImage=SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
		if(optimizedImage!=NULL) {
			Uint32 colorkey=SDL_MapRGB(optimizedImage->format, 0, 0xFF,0xFF);
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
		}
	}
	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip=NULL) {
	SDL_Rect offset;
	offset.x=x;
	offset.y=y;
	SDL_BlitSurface(source, clip, destination, &offset);
}

int main(int argc, char* argv[]) {
	clip[0].x=0;
	clip[0].y=0;
	clip[0].w=100;
	clip[0].h=100;
	clip[1].x=100;
	clip[1].y=0;
	clip[1].w=100;
	clip[1].h=100;
	clip[2].x=0;
	clip[2].y=100;
	clip[2].w=100;
	clip[2].h=100;
	clip[3].x=100;
	clip[3].y=100;
	clip[3].w=100;
	clip[3].h=100;
	
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1) {
		return 1;
	}
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return 1;
	}
	SDL_WM_SetCaption("Clipping", NULL);
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
	dots=load_image("dots.png");
	apply_surface(0, 0, dots, screen, &clip[0]);
	apply_surface(540, 0, dots, screen, &clip[1]);
	apply_surface(0, 380, dots, screen, &clip[2]);
	apply_surface(540, 380, dots, screen, &clip[3]);
	if(SDL_Flip(screen)==-1) {
		return 1;
	}
	SDL_Delay(10000);

	return 0;
}

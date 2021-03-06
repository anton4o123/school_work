#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

SDL_Surface* load_image(std::string filename) {
	SDL_Surface* loadedImage=NULL;
	SDL_Surface* optimizedImage=NULL;
	
	loadedImage=IMG_Load(filename.c_str());
	if(loadedImage!=NULL) {
		optimizedImage=SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	
	return optimizedImage;	
}

int main(int argc, char* argv[]) {

	return 0;
}

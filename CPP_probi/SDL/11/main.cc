#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "basic.hh"

SDL_Surface* screen=NULL;
SDL_Surface* background=NULL;
SDL_Surface* message=NULL;
SDL_Event event;
TTF_Font* font=NULL;
Mix_Music* music=NULL;
Mix_Chunk* scratch=NULL;
Mix_Chunk* high=NULL;
Mix_Chunk* med=NULL;
Mix_Chunk* low=NULL;
SDL_Color textColor={0, 0, 0};

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1 || TTF_Init()==-1 || Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096)==-1) {
		return false;
	}	
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return false;
	}
	SDL_WM_SetCaption("Monitor music", NULL);
	return true;
}

bool load_files() {
	background=load_image("background.png");
	font=TTF_OpenFont("lazy.ttf", 30);
	music=Mix_LoadMUS("beat.wav");
	scratch=Mix_LoadWAV("scratch.wav");
	high=Mix_LoadWAV("high.wav");
	med=Mix_LoadWAV("medium.wav");
	low=Mix_LoadWAV("low.wav");
	if(background==NULL || font==NULL || music==NULL || scratch==NULL || high==NULL || med==NULL || low==NULL) {
		return false;
	}
	return true;
}

void clean_up() {
	SDL_FreeSurface(background);
	TTF_CloseFont(font);
	Mix_FreeMusic(music);
	Mix_FreeChunk(scratch);
	Mix_FreeChunk(high);
	Mix_FreeChunk(med);
	Mix_FreeChunk(low);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	bool quit=false;
	if(init()==false || load_files()==false) {
		return 1;
	}
	apply_surface(0, 0, background, screen, NULL);
	message=TTF_RenderText_Solid(font, "Press 1, 2, 3 or 4 to play a sound effect", textColor);
	if(message==NULL) {
		return 1;
	}
	apply_surface((SCREEN_WIDTH-message->w)/2, 100, message, screen, NULL);
	SDL_FreeSurface(message);
	message=TTF_RenderText_Solid(font, "Press 9 to play or pause the music", textColor);
	if(message==NULL) {
		return 1;
	}
	apply_surface((SCREEN_WIDTH-message->w)/2, 200, message, screen, NULL);
	SDL_FreeSurface(message);
	message=TTF_RenderText_Solid(font, "Press 0 to stop the music", textColor);
	if(message==NULL) {
		return 1;
	}
	apply_surface((SCREEN_WIDTH-message->w)/2, 300, message, screen, NULL);
	SDL_FreeSurface(message);
	if(SDL_Flip(screen)==-1) {
		return 1;
	}
	
	while(quit==false) {
		while(SDL_PollEvent(&event)) {
			if(event.type==SDL_KEYDOWN) {
				if(event.key.keysym.sym==SDLK_1) {
					if(Mix_PlayChannel(-1, scratch, 0)==-1) {
						return 1;
					}
				} else if(event.key.keysym.sym==SDLK_2) {
					if(Mix_PlayChannel(-1, high, 0)==-1) {
						return 1;
					}
				} else if(event.key.keysym.sym==SDLK_3) {
					if(Mix_PlayChannel(-1, med, 0)==-1) {
						return 1;
					}
				} else if(event.key.keysym.sym==SDLK_4) {
					if(Mix_PlayChannel(-1, low, 0)==-1) {
						return 1;
					}
				} else if(event.key.keysym.sym==SDLK_9) {
					if(Mix_PlayingMusic()==0) {
						if(Mix_PlayMusic(music, -1)==-1) {
							return 1;
						}
					} else {
						if(Mix_PausedMusic()==1) {
							Mix_ResumeMusic();
						} else {
							Mix_PauseMusic();
						}
					}
				} else if(event.key.keysym.sym==SDLK_0) {
					Mix_HaltMusic();
				}
			} else if(event.type==SDL_QUIT) {
				quit=true;
			}
		}
	}
	
	clean_up();
	return 0;
}

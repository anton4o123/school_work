#include "../headers/basic.hh"
#include "string_input.hh"

SDL_Surface* screen=NULL;
SDL_Surface* background=NULL;
SDL_Surface* message=NULL;
TTF_Font* font=NULL;

SDL_Event event;
SDL_Color textColor={255, 255, 255};

StringInput::StringInput() {
	input="";
	text=NULL;
}

StringInput::~StringInput() {
	SDL_FreeSurface(text);
}

void StringInput::handle_input() {
	if(event.type==SDL_KEYDOWN) {
		std::string temp=input;
		
		if(input.length()<=16) {
			if(event.key.keysym.unicode==(Uint16)' ') {
				input+=(char)event.key.keysym.unicode;
			} else if(event.key.keysym.unicode>=(Uint16)'0' && event.key.keysym.unicode<=(Uint16)'9') {
				input+=(char)event.key.keysym.unicode;
			} else if(event.key.keysym.unicode>=(Uint16)'A' && event.key.keysym.unicode<=(Uint16)'Z') {
				input+=(char)event.key.keysym.unicode;
			} else if(event.key.keysym.unicode>=(Uint16)'a' && event.key.keysym.unicode<=(Uint16)'z') {
				input+=(char)event.key.keysym.unicode;
			}
		}
		
		if(event.key.keysym.sym==SDLK_BACKSPACE && input.length()!=0) {
			input.erase(input.length()-1);
		}
		
		if(input!=temp) {
			SDL_FreeSurface(text);
			text=TTF_RenderText_Solid(font, input.c_str(), textColor);
		}
	}
}

void StringInput::show_centered() {
	if(text!=NULL) {
		apply_surface((SCREEN_WIDTH-text->w)/2, (SCREEN_HEIGHT-text->h)/2, text, screen, NULL);
	}
}

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1 || TTF_Init()==-1) {
		return false;
	}
	SDL_EnableUNICODE(SDL_ENABLE);
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return false;
	}
	SDL_WM_SetCaption("Write your name", NULL);
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
	SDL_EnableUNICODE(SDL_DISABLE);
	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	bool quit=false, nameEntered=false;
	StringInput name;
	
	if(init()==false || load_files()==false) {
		return 1;
	}
	
	message=TTF_RenderText_Solid(font, "New HIGH score! Enter name:", textColor);
	while(quit==false) {
		while(SDL_PollEvent(&event)) {
			if(nameEntered==false) {
				name.handle_input();
				if(event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_RETURN) {
					nameEntered=true;
					SDL_FreeSurface(message);
					message=TTF_RenderText_Solid(font, "Rank 1st", textColor);
				}
			}
			if(event.type==SDL_QUIT) {
				quit=true;
			}
		}
		
		apply_surface(0, 0, background, screen, NULL);
		apply_surface((SCREEN_WIDTH-message->w)/2, ((SCREEN_HEIGHT/2)-message->h)/2, message, screen, NULL);
		name.show_centered();
		if(SDL_Flip(screen)==-1) {
			return 1;
		}
	}
	
	clean_up();
	return 0;
}

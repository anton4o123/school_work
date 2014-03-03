#include "foo.hh"
#include "../headers/timer.hh"

const int FRAMES_PER_SECOND=10;
const int FOO_WIDTH=64;
const int FOO_HEIGHT=205;
const int FOO_RIGHT=0;
const int FOO_LEFT=1;

SDL_Surface* screen=NULL;
SDL_Surface* foo=NULL;
SDL_Event event;
SDL_Rect clipsRight[4];
SDL_Rect clipsLeft[4];

void set_clips() {
	clipsRight[0].x=0;
	clipsRight[0].y=0;
	clipsRight[0].w=FOO_WIDTH;
	clipsRight[0].h=FOO_HEIGHT;
	
	clipsRight[1].x=FOO_WIDTH;
	clipsRight[1].y=0;
	clipsRight[1].w=FOO_WIDTH;
	clipsRight[1].h=FOO_HEIGHT;
	
	clipsRight[2].x=FOO_WIDTH*2;
	clipsRight[2].y=0;
	clipsRight[2].w=FOO_WIDTH;
	clipsRight[2].h=FOO_HEIGHT;
	
	clipsRight[3].x=FOO_WIDTH*3;
	clipsRight[3].y=0;
	clipsRight[3].w=FOO_WIDTH;
	clipsRight[3].h=FOO_HEIGHT;
	
	clipsLeft[0].x=0;
	clipsLeft[0].y=FOO_HEIGHT;
	clipsLeft[0].w=FOO_WIDTH;
	clipsLeft[0].h=FOO_HEIGHT;
	
	clipsLeft[1].x=FOO_WIDTH;
	clipsLeft[1].y=FOO_HEIGHT;
	clipsLeft[1].w=FOO_WIDTH;
	clipsLeft[1].h=FOO_HEIGHT;
	
	clipsLeft[2].x=FOO_WIDTH*2;
	clipsLeft[2].y=FOO_HEIGHT;
	clipsLeft[2].w=FOO_WIDTH;
	clipsLeft[2].h=FOO_HEIGHT;
	
	clipsLeft[3].x=FOO_WIDTH*3;
	clipsLeft[3].y=FOO_HEIGHT;
	clipsLeft[3].w=FOO_WIDTH;
	clipsLeft[3].h=FOO_HEIGHT;
}

Foo::Foo() {
	offSet=0;
	velocity=0;
	frame=0;
	status=FOO_RIGHT;
}

void Foo::handle_events() {
	if(event.type==SDL_KEYDOWN) {
		switch(event.key.keysym.sym) {
			case SDLK_RIGHT: velocity+=FOO_WIDTH/4;break;
			case SDLK_LEFT: velocity-=FOO_WIDTH/4;break;
		}
	} else if(event.type==SDL_KEYUP) {
		switch(event.key.keysym.sym) {
			case SDLK_RIGHT: velocity-=FOO_WIDTH/4;break;
			case SDLK_LEFT: velocity+=FOO_WIDTH/4;break;
		}
	}
}

void Foo::move() {
	offSet+=velocity;
	if(offSet<0 || offSet+FOO_WIDTH>SCREEN_WIDTH) {
		offSet-=velocity;
	}
}

void Foo::show() {
	if(velocity<0) {
		status=FOO_LEFT;
		frame++;
	} else if(velocity>0) {
		status=FOO_RIGHT;
		frame++;
	} else {
		frame=0;
	}
	
	if(frame>=4) {
		frame=0;
	}
	
	if(status==FOO_RIGHT) {
		apply_surface(offSet, SCREEN_HEIGHT-FOO_HEIGHT, foo, screen, &clipsRight[frame]);
	} else if(status==FOO_LEFT) {
		apply_surface(offSet, SCREEN_HEIGHT-FOO_HEIGHT, foo, screen, &clipsLeft[frame]);
	}
}

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1) {
		return false;
	}
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return false;
	}
	SDL_WM_SetCaption("The moving stick", NULL);
	return true;
}

bool load_files() {
	foo=load_image("foo.png");
	if(foo==NULL) {
		return false;
	}
	return true;
}

void clean_up() {
	SDL_FreeSurface(foo);
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	bool quit=false;
	Timer fps;
	Foo walk;
	set_clips();
	
	if(init()==false || load_files()==false) {
		return 1;
	}
	
	while(quit==false) {
		fps.start();
		while(SDL_PollEvent(&event)) {
			walk.handle_events();
			if(event.type==SDL_QUIT) {
				quit=true;
			}
		}
		walk.move();
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
		walk.show();
		if(SDL_Flip(screen)==-1) {
			return 1;
		}
		if(fps.get_ticks()<1000/FRAMES_PER_SECOND) {
			SDL_Delay((1000/FRAMES_PER_SECOND)-fps.get_ticks());
		}
	}
	
	clean_up();
	return 0;
}

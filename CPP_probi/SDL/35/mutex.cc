#include "../headers/basic.hh"
#include "SDL/SDL_thread.h"

SDL_Surface *screen=NULL;
SDL_Surface *images[5]={NULL, NULL, NULL, NULL, NULL};
SDL_Surface *buffer=NULL;

SDL_Event event;

SDL_Thread *producerThread=NULL;
SDL_Thread *consumerThread=NULL;

SDL_mutex *bufferLock=NULL;

SDL_cond *canProduce=NULL;
SDL_cond *canConsume=NULL;

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1) {
		return false;
	}
	
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen==NULL) {
		return false;
	}
	
	bufferLock=SDL_CreateMutex();
	canProduce=SDL_CreateCond();
	canConsume=SDL_CreateCond();
	
	SDL_WM_SetCaption("Producer/Consumer", NULL);
	return true;
}

bool load_files() {
	images[0]=load_image("1.png");
	images[1]=load_image("2.png");
	images[2]=load_image("3.png");
	images[3]=load_image("4.png");
	images[4]=load_image("5.png");
	
	if((images[0]==NULL) || (images[1]==NULL) || (images[2]==NULL) || (images[3]==NULL) || (images[4]==NULL)) {
		return false;
	}
	return true;
}

void clean_up() {
	SDL_DestroyMutex(bufferLock);
	SDL_DestroyCond(canProduce);
	SDL_DestroyCond(canConsume);
	
	for(int i=0;i<5;++i) {
		SDL_FreeSurface(images[i]);
	}
	SDL_Quit();
}

void produce(int x, int y) {
	SDL_mutexP(bufferLock);
	if(buffer!=NULL) {
		SDL_CondWait(canProduce, bufferLock);
	}
	
	buffer=images[rand()%5];
	apply_surface(x, y, buffer, screen, NULL);
	SDL_Flip(screen);
	
	SDL_mutexV(bufferLock);
	SDL_CondSignal(canConsume);
}

void consume(int x, int y) {
	SDL_mutexP(bufferLock);
	if(buffer==NULL) {
		SDL_CondWait(canConsume, bufferLock);
	}
	
	apply_surface(x, y, buffer, screen, NULL);
	buffer=NULL;
	SDL_Flip(screen);
	
	SDL_mutexV(bufferLock);
	SDL_CondSignal(canProduce);
}

int producer(void *data) {
	int y=10;
	srand(SDL_GetTicks());
	
	for(int p=0;p<5;++p) {
		SDL_Delay(rand()%1000);
		produce(10, y);
		y+=90;
	}
	return 0;
}

int consumer(void *data) {
	int y=10;
	
	for(int p=0;p<5;++p) {
		SDL_Delay(rand()%1000);
		consume(330, y);
		y+=90;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	bool quit=false;
	
	if(!init() || !load_files()) {
		return 1;
	}
	
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x80, 0x80, 0x80));
	if(SDL_Flip(screen)==-1) {
		return 1;
	}
	
	producerThread=SDL_CreateThread(producer, NULL);
	consumerThread=SDL_CreateThread(consumer, NULL);
	
	SDL_WaitThread(producerThread, NULL);
	SDL_WaitThread(consumerThread, NULL);
	
	while(!quit) {
		while(SDL_PollEvent(&event)) {
			if(event.type==SDL_QUIT) {
				quit=true;
			}
		}
	}

	clean_up();
	return 0;
}

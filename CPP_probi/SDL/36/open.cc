#include <iostream>
#include "../headers/basic.hh"
#include "../headers/timer.hh"
using namespace std;

const int FRAMES_PER_SECOND=60;

bool renderQuad;
SDL_Event event;

bool initGL() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.f, 0.f, 0.f, 1.f);
	GLenum error=glGetError();
	if(error!=GL_NO_ERROR) {
		cout << "Error initializing OpenGL! " <<  gluErrorString(error) << endl;
		return false;
	}
	
	return true;
}

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1) {
		return false;
	}
	
	if(SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL)==NULL) {
		return false;
	}

	if(!initGL()) {
		return false;
	}
	
	SDL_WM_SetCaption("Open GL Test", NULL);
	
	return true;
}

void handleKeys(unsigned char key) {
	if(key=='q') {
		renderQuad=!renderQuad;
	}
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT);

	if(renderQuad) {
		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(-0.5f, 0.5f);
		glEnd();
	}

	SDL_GL_SwapBuffers();
}

int main(int argc, char* argv[]) {
	Timer fps;

	if(!init()) {
		return 1;
	}

	while(true) {
		fps.start();
		if(SDL_PollEvent(&event)) {
			if(event.type==SDL_QUIT) {
				break;
			} else if(event.type==SDL_KEYDOWN) {
				handleKeys(event.key.keysym.sym);
			}
			render();
		}

		if(fps.get_ticks()<1000.f/FRAMES_PER_SECOND) {
			SDL_Delay(1000.f/FRAMES_PER_SECOND-fps.get_ticks());
		}
	}

	return 0;
}
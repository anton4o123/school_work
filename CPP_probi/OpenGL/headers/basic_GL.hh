#ifndef BASIC_GL_HH__
#define BASIC_GL_HH__

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
using namespace std;

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
const int SCREEN_FPS=60;

bool initGL();
void update();
void render();

#endif
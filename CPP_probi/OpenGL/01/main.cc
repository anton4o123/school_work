#include "../headers/basic_GL.hh"

void runMainLoop(int val) {
	update();
	render();
	glutTimerFunc(1000.f/SCREEN_FPS, runMainLoop, val);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
//	glutInitContexVersion(2, 1);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("OpenGL");

	if(!initGL()) {
		cout << "Unable to initialize graphics library!" << endl;
		return 1;
	}

	glutDisplayFunc(render);
	glutTimerFunc(1000.f/SCREEN_FPS, runMainLoop, 0);
	glutMainLoop();
	return 0;
}
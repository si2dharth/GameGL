#include "gameStd.h"

#include <Windows.h>
#include <gl/freeglut.h>

namespace GameWindow {
	string title = "Game Window";
	int width = 640, height = 480;
	int posX = -1, posY = -1;
	int windowID = -1;
	unsigned int mode = GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE;

	namespace EventHandlers {
		EventHandler
			mouse,
			draw,
			draw2D,
			drawn2D,
			draw3D,
			drawn3D,
			resize,
			mouseMove,
			mouseDrag,
			mouseEnter,
			mouseLeave,
			windowVisible,
			windowHidden,
			keyPress,
			idle,
			timer;
	};
	EventHandler &mouseHandler() { return EventHandlers::mouse; }
	EventHandler &drawHandler() { return EventHandlers::draw; }
	EventHandler &resizeHandler() { return EventHandlers::resize; }
	EventHandler &mouseMoveHandler() { return EventHandlers::mouseMove; }
	EventHandler &mouseDragHandler() { return EventHandlers::mouseDrag; }
	EventHandler &mouseEnterHandler() { return EventHandlers::mouseEnter; }
	EventHandler &mouseLeaveHandler() { return EventHandlers::mouseLeave; }
	EventHandler &windowVisibleHandler() { return EventHandlers::windowVisible; }
	EventHandler &windowHiddenHandler() { return EventHandlers::windowHidden; }
	EventHandler &keyPressHandler() { return EventHandlers::keyPress; }
	EventHandler &idleHandler() { return EventHandlers::idle; }
	EventHandler &timerHandler() { return EventHandlers::timer; }
	EventHandler &draw2DHandler() { return EventHandlers::draw2D; }
	EventHandler &draw3DHandler() { return EventHandlers::draw3D; }
	EventHandler &drawn2DHandler() { return EventHandlers::drawn2D; }
	EventHandler &drawn3DHandler() { return EventHandlers::drawn3D; }

	void switch3D() {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
	}

	void stop3D() {
		glPopMatrix();
	}

	void switch2D() {
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, width, height, 0, -1.0, 10.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_CULL_FACE);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void stop2D() {
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}

	void setTitle(string title) {
		GameWindow::title = title;
		if (windowID >= 0) {
			glutSetWindowTitle(title.c_str());
		}
	}

	void setSize(int width, int height) {
		GameWindow::width = width;
		GameWindow::height = height;
		if (windowID >= 0) {
			glutReshapeWindow(width, height);
		}
	}

	void setPosition(int posX, int posY) {
		GameWindow::posX = posX;
		GameWindow::posY = posY;
		if (windowID >= 0) {
			glutPositionWindow(posX, posY);
		}
	}

	void setMode(unsigned int mode) {
		GameWindow::mode = mode;
	}

	void drawCallback() {
		//EventHandlers::draw.raise();
		switch3D();
		EventHandlers::draw3D.raise();
		EventHandlers::drawn3D.raise();
		stop3D();
		switch2D();
		EventHandlers::draw2D.raise();
		EventHandlers::drawn2D.raise();		
		stop2D();
		glutSwapBuffers();
	}

	void clearWindow() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void windowResized(int w, int h) {
		width = w;
		height = h;
		EventHandlers::resize.raise(w, h);
	}

	void mouseEvent(int button, int state, int x, int y) {
		EventHandlers::mouse.raise(button, state, x, y);
	}

	void mouseMove(int x, int y) {
		EventHandlers::mouseMove.raise(x, y);
	}

	void mouseDrag(int x, int y) {
		EventHandlers::mouseDrag.raise(x, y);
	}

	void windowMouse(int enter) {
		if (enter == GLUT_ENTERED)
			EventHandlers::mouseEnter.raise();
		else
			EventHandlers::mouseLeave.raise();
	}

	void windowVisibility(int visible) {
		if (visible == GLUT_VISIBLE)
			EventHandlers::windowVisible.raise();
		else
			EventHandlers::windowHidden.raise();
	}

	void keyPress(unsigned char key, int x, int y) {
		EventHandlers::keyPress.raise(key, x, y);
	}

	void idle() {
		EventHandlers::idle.raise();
	}

	void timer(int val) {
		EventHandlers::timer.raise(val);
	}
};

using namespace GameWindow;

void main(int nargs, char **args) {
	glutInit(&nargs, args);
	setup(nargs, args);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(posX, posY);
	glutInitDisplayMode(mode);
	windowID = glutCreateWindow(title.c_str());
	glutDisplayFunc(drawCallback);
	glutMouseFunc(mouseEvent);
	glutMotionFunc(mouseDrag);
	glutPassiveMotionFunc(mouseMove);
	glutKeyboardFunc(keyPress);
	glutVisibilityFunc(windowVisibility);
	glutIdleFunc(idle);
	glutReshapeFunc(windowResized);
	glutEntryFunc(windowMouse);

	glMatrixMode(GL_PROJECTION);	// Setup perspective projection
	glLoadIdentity();
	gluPerspective(70, 1, 1, 40);

	glMatrixMode(GL_MODELVIEW);		// Setup model transformations
	glLoadIdentity();
	gluLookAt(0, 0, 5, 0, 0, -1, 0, 1, 0);

	//  Set default ambient light in scene
	float  amb[] = { 0, 0, 0, 1 };	// Ambient material property
	float  lt_amb[] = { 0.5, 0.5, 0.5, 1 };	// Ambient light property
	float  lt_dif[] = { 0.8, 0.8, 0.8, 1 };	// Ambient light property
	float  lt_spc[] = { 0, 0, 0, 1 };	// Specular light property
	float lt_pos[] = { 0.7, 1, 1.5, 0 };	// Light position

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	//  Set Light 0 position, ambient, diffuse, specular intensities

	glLightfv(GL_LIGHT0, GL_POSITION, lt_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lt_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lt_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lt_spc);

	//  Enable Light 0 and GL lighting

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	glShadeModel(GL_SMOOTH);		// Smooth shading
	glEnable(GL_NORMALIZE);		// Normalize normals

	glClearDepth(1.0);			// Setup background colour
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glutMainLoop();
}
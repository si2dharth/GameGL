#include "gameStd.h"

#include <Windows.h>
#include <gl/freeglut.h>

namespace GameWindow {
	string title = "Game Window";
	int width = 640, height = 480;
	int posX = -1, posY = -1;
	int windowID = -1;

	namespace EventHandlers {
		EventHandler
			mouse,
			draw,
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

	void drawCallback() {
		draw();
		EventHandlers::draw.raise();
		glutSwapBuffers();
	}

	void clearWindow() {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void windowResized(int w, int h) {
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

	glutMainLoop();
}
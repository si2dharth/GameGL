#include "gameStd.h"
#include "gameCamera.h"
#include <iostream>
#include <gl/freeglut.h>
using namespace std;
using namespace GameWindow;


void mouseEntered() {
	cout << "ENTERED " << endl;
}

void mouseLeft() {
	cout << "LEFT" << endl;
}

void mouseMove(int x, int y) {
	cout << x << ", " << y << endl;
}


bool mouseE = true;
void mouseDrag(int x, int y) {
	if (mouseE) {
		mouseE = false;
		mouseMoveHandler() -= func(mouseMove);
	}
	cout << x << ", " << y << " CLiCKeD" << endl;
}

class MouseCamera : public GameCamera3D {
	float camRotX = 0.765, camRotY = 0.765, camDist = 5;
	int mouseX = 0, mouseY = 0;
	bool btnPressed = false;
	void updateMouseState(int button, int state, int x, int y) {
		if (button == GLUT_LEFT_BUTTON) btnPressed = (state == GLUT_DOWN);
		mouseX = x;
		mouseY = glutGet(GLUT_WINDOW_HEIGHT) - y;
	}

	void positionCamera() {
		setPosition(camDist * cos(camRotX) * sin(camRotY), camDist * cos(camRotY), camDist * sin(camRotX) *sin(camRotY));
	}

	void refreshPos(int x, int y) {
		if (btnPressed) {
			y = glutGet(GLUT_WINDOW_HEIGHT) - y;
			float x_ratchet = glutGet(GLUT_WINDOW_WIDTH) / 10.0;
			float y_ratchet = glutGet(GLUT_WINDOW_HEIGHT) / 10.0;
			camRotX += (float)(x - mouseX) / x_ratchet;
			camRotY += (float)(y - mouseY) / y_ratchet;

			if (camRotX > 6.2856) camRotX -= 6.2856;				//Reset the rotation every 2*PI rotations
			if (camRotX < 0) camRotX += 6.2856;
			if (camRotY < 0.02) camRotY = 0.02;						//Limit rotation from 0 to PI.
			if (camRotY > 3.14) camRotY = 3.14;

			positionCamera();					//Update the location of camera in cartesian coordinates.
			glutPostRedisplay();
			mouseX = x;
			mouseY = y;
		}
	}

public:
	MouseCamera() : GameCamera3D() {
		mouseHandler() += func(this, &MouseCamera::updateMouseState);
		mouseDragHandler() += func(this, &MouseCamera::refreshPos);
		positionCamera();
	}
	~MouseCamera() {
		mouseHandler() -= func(this, &MouseCamera::updateMouseState);
		mouseDragHandler() -= func(this, &MouseCamera::refreshPos);
	}
};

class KeyCamera2D : public GameCamera2D {
	
	void moveCam(int key) {
		unsigned char k = key;
		switch (k) {
		case 'W':
		case 'w':
			setPosition(posX, posY - 10);
			break;
		case 'S':
		case 's':
			setPosition(posX, posY + 10);
			break;
		case 'A':
		case 'a':
			setPosition(posX - 10, posY);
			break;
		case 'D':
		case 'd':
			setPosition(posX + 10, posY);
			break;
		}
		glutPostRedisplay();
	}
public:
	KeyCamera2D() : GameCamera2D() {
		keyPressHandler() += func(this, &KeyCamera2D::moveCam);
	}

	~KeyCamera2D() {
		keyPressHandler() -= func(this, &KeyCamera2D::moveCam);
	}
};

void draw2d();

MouseCamera cam;
KeyCamera2D cam2D;
void setup(int nargs, char **args) {
	setTitle("Hello World");
	setSize(500,500);
	mouseEnterHandler() += func(mouseEntered);
	mouseLeaveHandler() += func(mouseLeft);
	mouseMoveHandler() += func(mouseMove);
	mouseDragHandler() += func(mouseDrag);	
	draw3DHandler() += func(draw);
	draw2DHandler() += func(draw2d);
//	cam2D.setPosition(-250, -250);
//	cam.lookAt(0.2, 0, 5);
	//cam.setPosition(-3, 2, -3);
	//cam.setPosition(0, 2.828,- 2.828);
	//cam.lookAt(1.0, 0.0, 0);
//	cam.setPosition(0, -1);
	
}

void draw() {
	clearWindow();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	float red[] = { 1,0,0 }, blue[] = { 0,0, 1}, green[] = { 0,1,0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
	glBegin(GL_LINES);
	glVertex3f(-100, 0, 0);
	glVertex3f(100, 0, 0);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green);
	glBegin(GL_LINES);
	glVertex3d(0, -100, 0);
	glVertex3d(0, 100, 0);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
	glBegin(GL_LINES);
	glVertex3d(0, 0, -100);
	glVertex3d(0, 0, 100);
	glEnd();

	glutSolidCube(2);
	glPopMatrix();
}

void draw2d() {
	float yellow[] = { 1,1,0 }, cyan[] = { 0,1,1 };
	glBegin(GL_LINES);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, yellow);
	glVertex2f(-500, 0);
	glVertex2f(500, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cyan);
	glVertex2f(0, -500);
	glVertex2f(0, 500);
	glEnd();
	glRectf(0, 0, 200, 100);
}
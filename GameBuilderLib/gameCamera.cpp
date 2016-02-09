#include "gameCamera.h"
#include <GL/freeglut.h>

GameCamera::GameCamera() {}

GameCamera::~GameCamera() {}

GameCamera2D::GameCamera2D() : GameCamera(), posX(0), posY(0) {
	GameWindow::draw2DHandler() += func(this, &GameCamera2D::setCam);
	GameWindow::drawn2DHandler() += func(this, &GameCamera2D::resetCam);
}

GameCamera2D::~GameCamera2D() {
	GameWindow::draw2DHandler() -= func(this, &GameCamera2D::setCam);
	GameWindow::drawn2DHandler() -= func(this, &GameCamera2D::resetCam);
}

void GameCamera2D::setPosition(int x, int y) {
	posX = x;
	posY = y;
}

void GameCamera2D::setCam() {
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(-posX, -posY, 1);
}

void GameCamera2D::resetCam() {
	glPopMatrix();
}

GameCamera3D::GameCamera3D() : GameCamera(), posX(0), posY(0), posZ(-1), lookX(0), lookY(0), lookZ(0) {
	GameWindow::draw3DHandler() += func(this, &GameCamera3D::setCam);
	GameWindow::drawn3DHandler() += func(this, &GameCamera3D::resetCam);
}

GameCamera3D::~GameCamera3D() {
	GameWindow::draw3DHandler() -= func(this, &GameCamera3D::setCam);
	GameWindow::drawn3DHandler() -= func(this, &GameCamera3D::resetCam);
}

void GameCamera3D::setPosition(float x, float y, float z) {
	posX = x;
	posY = y;
	posZ = z;
}

void GameCamera3D::lookAt(float x, float y, float z) {
	lookX = x;
	lookY = y;
	lookZ = z;
}

void GameCamera3D::setCam() {
	gluLookAt(posX, posY, posZ, lookX, lookY, lookZ, 0, 1, 0);
}

void GameCamera3D::resetCam() {
}
#pragma once
#include "Common.h"
#include "EventAdapter.h"


void setup(int nargs, char **args);

void draw();

namespace GameWindow {

	void setTitle(string title);
	void setSize(int width, int height);
	void setPosition(int posX, int posY);

	void clearWindow();

	typedef void(*funcPtr)();
	typedef void(*funcPtrInt)(int);
	typedef void(*funcPtrInt2)(int, int);
	typedef void(*funcPtrInt3)(int, int, int);
	typedef void(*funcPtrInt4)(int, int, int, int);

	EventHandler &mouseHandler();
	EventHandler &drawHandler();
	EventHandler &draw2DHandler();
	EventHandler &draw3DHandler();
	EventHandler &drawn2DHandler();
	EventHandler &drawn3DHandler();
	EventHandler &resizeHandler();
	EventHandler &mouseMoveHandler();
	EventHandler &mouseDragHandler();
	EventHandler &mouseEnterHandler();
	EventHandler &mouseLeaveHandler();
	EventHandler &windowVisibleHandler();
	EventHandler &windowHiddenHandler();
	EventHandler &keyPressHandler();
	EventHandler &idleHandler();
	EventHandler &timerHandler();
};
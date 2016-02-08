#include "gameStd.h"
#include <iostream>
using namespace std;
using namespace GameWindow;


class TestObj {
public:
	void func1() {

	}

	void func2(int i) {
		cout << (char)i << endl;
	}

	void func3(int i, int j) {
		cout << i << " " << j << endl;
	}

	void func4(int i, int j, int k, int l) {
		
	}

};

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

void setup(int nargs, char **args) {
	setTitle("Hello World");
	setSize(480, 640);
	mouseEnterHandler() += func(mouseEntered);
	mouseLeaveHandler() += func(mouseLeft);
	mouseMoveHandler() += func(mouseMove);
	mouseDragHandler() += func(mouseDrag);
}

void draw() {
	clearWindow();
}
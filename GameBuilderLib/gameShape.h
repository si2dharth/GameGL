#pragma once


class Shape {
	float originX, originY, originZ;
public:
	void translate(float x, float y, float z);
	virtual void draw();
};
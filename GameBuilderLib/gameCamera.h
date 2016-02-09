#pragma once
#include "gameStd.h"

class GameCamera {
public:
	GameCamera();
	virtual ~GameCamera();
};

class GameCamera2D : public GameCamera {
	void setCam();
	void resetCam();
protected:
	int posX, posY;

public:
	GameCamera2D();
	virtual ~GameCamera2D();
	void setPosition(int x, int y);
	
};

class GameCamera3D : public GameCamera {
	void setCam();
	void resetCam();
	float posX, posY, posZ;
	float lookX, lookY, lookZ;
public:
	GameCamera3D();
	virtual ~GameCamera3D();
	void setPosition(float x, float y, float z);
	void lookAt(float x, float y, float z);
};
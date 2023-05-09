#pragma once
#include "GameObject.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "LogTime.h"
class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();
	void Init(int x, int y, int w, int h, int R, int G, int B);
	virtual void Input();
	virtual void Update();
	virtual void Render(SDL_Renderer* rend);
	virtual void Clean();
	virtual void setBorders(int x, int y);
	virtual SDL_Rect getRect();
	void setDirection(bool direction);
	virtual bool getFlip();
private:
	SDL_Rect enemyRect;
	Vector2D posVec;
	Vector2D velVec;
	int move;
	bool right;
	int windowX;
	int windowY;
	bool flip;
	char logMessage[32];
};


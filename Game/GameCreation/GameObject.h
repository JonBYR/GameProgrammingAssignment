#pragma once
#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_mixer.h"
#include "Vector2D.h"
class GameObject
{
public:
	void virtual Init(int x, int y, int w, int h, int R, int G, int B) = 0;
	virtual void Input() = 0;
	void virtual Render(SDL_Renderer* rend) = 0;
	void virtual Update() = 0;
	void virtual Clean() = 0;
	void virtual setBorders(int x, int y) = 0;
	SDL_Rect virtual getRect() = 0;
	bool virtual getFlip() = 0;
protected:
	int red, green, blue;
	Vector2D posVec;
	Vector2D velVec;
	Vector2D accVec; //vectors that will be inherited and used in other classes
};


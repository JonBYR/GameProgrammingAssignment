#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "SDL.h"
#include <stdlib.h>
#include <time.h>
#include "SimpleSprite.h"
#include "LogTime.h"
#include "Collision.h"
#include "SDL_mixer.h"
class Squares
{
public:
	Squares();
	~Squares();
	void Init(int eY, int eX, float eDirX, float eDirY, int eNum);
	void Input();
	void Update(SDL_Rect* playerRect);
	void Add(int x, int y, int num);
	void Render(SDL_Renderer* rend);
	void Clean();
	virtual void setBorders(int x, int y);
	void setMix(bool m);
	void setMix(int vol);
	bool getCollision();
	int scoreMultiplier(int score);
	void setFrogs(int frogs);
private:
	std::vector<GameObject*> objects;
	std::vector<SimpleSprite*> sprites;
	int X, Y, numb;
	float dirx, diry;
	char logMessage[32];
	int extraScore;
	int wX;
	int wY;
	Mix_Chunk* GOOD_FROG;
	Mix_Chunk* BAD_FROG;
	int startVol;
	bool collision;
	static bool audio;
};


#pragma once
#include "GameObject.h"
#include <iostream>
#include "LogTime.h"
class Player : public GameObject
{
public:
	Player();
	~Player();
	void Init(int x, int y, int w, int h, int R, int G, int B);
	virtual void Input();
	virtual void Update();
	virtual void Render(SDL_Renderer* rend);
	virtual void Clean();
	bool isKeyDown(SDL_Scancode key);
	virtual void setBorders(int x, int y);
	virtual SDL_Rect getRect();
	void SetMix(bool m);
	void SetMix(int vol);
	virtual bool getFlip();
private:
	SDL_Rect playerRect;
	SDL_Rect spriteRect;
	const Uint8* keyState;
	int windowX, windowY;
	bool jump = false;
	SDL_Surface* surface;
	SDL_Texture* texture;
	char logMessage[32];
	//Mix_Chunk* SOUND_jump = NULL;
	int startVol;
	bool flip;
};


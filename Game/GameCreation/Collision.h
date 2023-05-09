#pragma once
#include "SDL.h"
class Collision
{
public:
	const static int buffer = 4;
	static bool rectCollider(SDL_Rect* playerRect, SDL_Rect* enemyRect);
};


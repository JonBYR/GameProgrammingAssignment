#include "Enemy.h"
Enemy::Enemy() {}
void Enemy::Input()
{

}
void Enemy::Init(int x, int y, int w, int h, int R, int G, int B)
{
	enemyRect.x = x;
	enemyRect.y = y;
	enemyRect.w = w;
	enemyRect.h = h;
	red = R;
	green = G;
	blue = B;
	posVec.setX(x);
	posVec.setY(y);
	velVec.setX(0);
	velVec.setY(0);
	move = rand() % 10 + 1;
	right = true;
	flip = false;
	LogTime::getTime(logMessage, 32);
}
void Enemy::Update()
{
	if (right) 
	{
		posVec.setX(posVec.getX() + move);
		velVec.setY(velVec.getY() + 1);
		flip = false;
	}
	if (!right) 
	{
		posVec.setX(posVec.getX() - move);
		velVec.setY(velVec.getY() + 1);
		flip = true;
	}
	if (enemyRect.y >= 500) 
	{
		velVec.setY(-20 - move);
	}
	posVec += velVec; //position of the rectangle is changed by the velocity vector
	enemyRect.x = posVec.getX();
	enemyRect.y = posVec.getY();
	if (enemyRect.x >= windowX)
	{
		right = false;
		flip = true;
		SDL_Log("[%s] [FROG BOUNDARY COLLISION] [%i]", logMessage, SDL_GetTicks());
		LogTime::write("FROG BOUNDARY COLLISION", SDL_GetTicks(), logMessage);
	}
	else if (enemyRect.x <= 0)
	{
		right = true;
		SDL_Log("[%s] [FROG BOUNDARY COLLISION] [%i]", logMessage, SDL_GetTicks());
		LogTime::write("FROG BOUNDARY COLLISION", SDL_GetTicks(), logMessage);
	}
}
void Enemy::Render(SDL_Renderer* rend)
{
	SDL_SetRenderDrawColor(rend, red, green, blue, 255);
	SDL_RenderDrawRect(rend, &enemyRect);
}
void Enemy::Clean()
{

}
SDL_Rect Enemy::getRect() 
{
	return enemyRect;
}
void Enemy::setBorders(int x, int y) 
{
	windowX = x;
	windowY = y;
}
void Enemy::setDirection(bool direction) 
{
	right = direction;
}
bool Enemy::getFlip() 
{
	return flip;
}
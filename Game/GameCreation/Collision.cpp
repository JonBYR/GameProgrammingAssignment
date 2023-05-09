#include "Collision.h"
bool Collision::rectCollider(SDL_Rect* playerRect, SDL_Rect* enemyRect) 
{
	int playerHBuf = playerRect->h / buffer;
	int playerWBuf = playerRect->w / buffer;
	int enemyHBuf = enemyRect->h / buffer;
	int enemyWBuf = enemyRect->w / buffer;
	if ((playerRect->y + playerRect->h) - playerHBuf <= (enemyRect->y + enemyHBuf)) {return false; } //bottom of player is less than top of enemy
	if ((playerRect->y + playerHBuf) >= (enemyRect->y + enemyRect->h)- enemyHBuf) { return false; } //top of player is more than bottom of enemy
	if ((playerRect->x + playerRect->w) - playerWBuf <= (enemyRect->x + enemyWBuf)) { return false; } //right of player is less than left of enemy
	if ((playerRect->x + playerWBuf) >= (enemyRect->x + enemyRect->w) - enemyWBuf) { return false; } //left of player is more than right of enemy
	else { return true; } //if all other conditions fail then the player has collided
}
#include "Player.h"
Player::Player() {}

void Player::Init(int x, int y, int w, int h, int R, int G, int B) 
{
	playerRect.x = x;
	playerRect.y = y;
	playerRect.w = w;
	playerRect.h = h;
	red = R;
	green = G;
	blue = B;
	posVec.setX(x);
	posVec.setY(y);
	velVec.setX(0);
	velVec.setY(0);
	LogTime::getTime(logMessage, 32);
	startVol = 128;
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		printf("Warning: Audio has not been found! \n");
		SDL_Quit();
	}
	else
	{
		SOUND_jump = Mix_LoadWAV("./content/PlayerJump.wav");
	}
	flip = false;
}
bool Player::isKeyDown(SDL_Scancode key) //checks that the type of input pressed on the keyboard is either true or false 
{
	if (keyState != 0) 
	{
		if (keyState[key] == 1) return true;
		else return false;
	}
}
void Player::setBorders(int x, int y)
{
	windowX = x;
	windowY = y;
}
void Player::Input()
{
	keyState = SDL_GetKeyboardState(0);
	if (isKeyDown(SDL_SCANCODE_RIGHT)) { velVec.setX(3); velVec.setY(0); SDL_Log("[%s] [PLAYER RIGHT] [%i]", logMessage, SDL_GetTicks()); LogTime::write("PLAYER RIGHT", SDL_GetTicks(), logMessage);}//checks the state of the keyboard, and if right, up, left or down is pressed then the velocity vector is adjusted accordingly
	if (isKeyDown(SDL_SCANCODE_LEFT)) {
		velVec.setX(-3); velVec.setY(0);
		SDL_Log("[%s] [PLAYER LEFT] [%i]", logMessage, SDL_GetTicks());
		LogTime::write("PLAYER LEFT", SDL_GetTicks(), logMessage);
	}
	if (isKeyDown(SDL_SCANCODE_UP)) { velVec.setY(-3); velVec.setX(0); SDL_Log("[%s] [PLAYER UP] [%i]", logMessage, SDL_GetTicks()); LogTime::write("PLAYER UP", SDL_GetTicks(), logMessage);}
	if (isKeyDown(SDL_SCANCODE_DOWN)) {
		velVec.setY(3); velVec.setX(0);
		SDL_Log("[%s] [PLAYER DOWN] [%i]", logMessage, SDL_GetTicks());
		LogTime::write("PLAYER DOWN", SDL_GetTicks(), logMessage);
	}
	if (isKeyDown(SDL_SCANCODE_RSHIFT)) 
	{
		velVec.setX(0);
		velVec.setY(0);
		SDL_Log("[%s] [PLAYER RSHIFT] [%i]", logMessage, SDL_GetTicks());
		LogTime::write("PLAYER RSHIFT", SDL_GetTicks(), logMessage);
	}
	if (isKeyDown(SDL_SCANCODE_SPACE)) 
	{
		jump = true;
		Mix_PlayChannel(-1, SOUND_jump, 0);
		SDL_Log("[%s] [PLAYER SPACE] [%i]", logMessage, SDL_GetTicks());
		LogTime::write("PLAYER SPACE", SDL_GetTicks(), logMessage);
	}
	if (isKeyDown(SDL_SCANCODE_LSHIFT) && velVec.getX() < 0) { accVec.setX(-1); SDL_Log("[%s] [PLAYER LSHIFT] [%i]", logMessage, SDL_GetTicks()); LogTime::write("PLAYER LSHIFT", SDL_GetTicks(), logMessage);}
	else if (isKeyDown(SDL_SCANCODE_LSHIFT) && velVec.getX() > 0) { accVec.setX(1); SDL_Log("[%s] [PLAYER LSHIFT] [%i]", logMessage, SDL_GetTicks()); LogTime::write("PLAYER LSHIFT", SDL_GetTicks(), logMessage);}
	else accVec.setX(0);
}
void Player::Update() 
{
	if (velVec.getX() < 0) flip = false;
	else if (velVec.getX() > 0) flip = true;
	velVec += accVec;
	posVec += velVec; //position of the rectangle is changed by the velcoity vector
	playerRect.x = posVec.getX();
	playerRect.y = posVec.getY();
	if (jump == true) 
	{
		if (posVec.getY() - 20 >= 0) posVec.setY(posVec.getY()-20);
		jump = false;
	}
	if ((playerRect.x >= windowX))
	{
		accVec.setX(0);
		velVec.setX(-1);
		posVec.setX(posVec.getX() - 10);
		SDL_Log("[%s] [PLAYER BOUNDARY COLLISION] [%i]", logMessage, SDL_GetTicks());
		LogTime::write("PLAYER BOUNDARY COLLISION", SDL_GetTicks(), logMessage);
	}
	if (playerRect.x <= 0)
	{
		accVec.setX(0);
		velVec.setX(1);
		posVec.setX(0);
		SDL_Log("[%s] [PLAYER BOUNDARY COLLISION] [%i]", logMessage, SDL_GetTicks());
		LogTime::write("PLAYER BOUNDARY COLLISION", SDL_GetTicks(), logMessage);
	}
	if ((playerRect.y >= windowY))
	{
		velVec.setY(-1);
		posVec.setY(posVec.getY() - 10);
		SDL_Log("[%s] [PLAYER BOUNDARY COLLISION] [%i]", logMessage, SDL_GetTicks());
		LogTime::write("PLAYER BOUNDARY COLLISION", SDL_GetTicks(), logMessage);
	}
	if (playerRect.y <= 0) 
	{ 
		velVec.setY(1); 
		posVec.setY(0);
		SDL_Log("[%s] [PLAYER BOUNDARY COLLISION] [%i]", logMessage, SDL_GetTicks());
		LogTime::write("PLAYER BOUNDARY COLLISION", SDL_GetTicks(), logMessage);
	}
	SDL_Log("[%s] [PLAYER UPDATE] [%i]", logMessage, SDL_GetTicks());
	LogTime::write("PLAYER UPDATE", SDL_GetTicks(), logMessage);
}
void Player::Render(SDL_Renderer* rend) 
{
	//texture = SDL_CreateTextureFromSurface(rend, surface);
	SDL_SetRenderDrawColor(rend, red, green, blue, 255);
	//SDL_RenderDrawRect(rend, &playerRect);
	//SDL_RenderCopy(rend, texture, &spriteRect, &playerRect);
}
SDL_Rect Player::getRect() 
{
	return playerRect;
}
void Player::Clean() 
{
	Mix_FreeChunk(SOUND_jump);
}
void Player::SetMix(bool m) 
{
	if (m == false) Mix_VolumeChunk(SOUND_jump, startVol);
	else Mix_VolumeChunk(SOUND_jump, 0);
}
void Player::SetMix(int vol) 
{
	if (startVol + vol > 128) return;
	if (startVol + vol < 0) return;
	Mix_VolumeChunk(SOUND_jump, startVol + vol);
}
bool Player::getFlip() 
{
	return flip;
}
Player::~Player() {}
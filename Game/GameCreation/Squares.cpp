#include "Squares.h"
bool Squares::audio = true;
Squares::Squares()
{
}
void Squares::Init(int eY, int eX, float eDirX, float eDirY, int eNum) 
{
	X = eX;
	Y = eY;
	dirx = eDirX;
	diry = eDirY;
	numb = eNum;
	for (int i = 0; i < numb; i++)
	{
		int PosX = X + (i * (dirx * 10));
		int PosY = Y + (i * (diry * 10));
		Add(PosX, PosY, i);
	}
	LogTime::getTime(logMessage, 32);
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		printf("Warning: Audio has not been found! \n");
		SDL_Quit();
	}
	else
	{
		GOOD_FROG = Mix_LoadWAV("./content/GoodFrog.wav");
		BAD_FROG = Mix_LoadWAV("./content/BadFrog.wav");
	}
	startVol = 128;
	setMix(audio);
}
void Squares::Add(int X, int Y, int num) 
{
	Enemy* newEnemy = new Enemy();
	SimpleSprite* newSprite = new SimpleSprite(0, 0, 32, 32, num);
	newEnemy->Init(X, Y, 50, 50, 0, 0, 255);
	newEnemy->setDirection(true);
	newEnemy->setBorders(wX, wY);
	objects.push_back(newEnemy);
	sprites.push_back(newSprite);
}
void Squares::Render(SDL_Renderer* rend) 
{
	for (int i = 0; i < objects.size(); i++) 
	{
		if ((sprites[i]->getNumber() % 2) == 0) sprites[i]->load(rend, "content/Frog 1.png");
		else sprites[i]->load(rend, "content/Frog 2.png");
		sprites[i]->render(rend, objects[i]->getRect(), objects[i]->getFlip());
		SDL_Log("[%s] [FROG RENDER %i] [%i]", logMessage, sprites[i]->getNumber() + 1, SDL_GetTicks());
		LogTime::write("FROG RENDER", SDL_GetTicks(), sprites[i]->getNumber() + 1, logMessage);
	}
}
void Squares::Update(SDL_Rect* playerRect) 
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update();
		SDL_Log("[%s] [FROG UPDATE %i] [%i]", logMessage, sprites[i]->getNumber() + 1, SDL_GetTicks());
		LogTime::write("FROG UPDATE", SDL_GetTicks(), sprites[i]->getNumber() + 1, logMessage);
		SDL_Rect enemyRect = objects[i]->getRect();
		if (Collision::rectCollider(playerRect, &enemyRect) == true)
		{
			SDL_Log("[%s] [PLAYER HAS COLLIDED WITH FROG %i] [%i]", logMessage, sprites[i]->getNumber() + 1, SDL_GetTicks());
			LogTime::write("PLAYER HAS COLLIDED WITH FROG", SDL_GetTicks(), sprites[i]->getNumber() + 1, logMessage);
			if ((sprites[i]->getNumber() % 2) == 0) { Mix_PlayChannel(-1, GOOD_FROG, 0); extraScore = 2; collision = true; }
			else if ((sprites[i]->getNumber() % 2) == 1)
			{
				Mix_PlayChannel(-1, BAD_FROG, 0); extraScore = 0; collision = true;
			}
			delete objects[i];
			delete sprites[i];
			objects.erase(objects.begin() + i);
			sprites.erase(sprites.begin() + i);
		}
		if (objects.size() == 0) 
		{
			Init(50, 0, 10.0, 10.0, numb);
			SDL_Log("[%s] [MORE FROGS SPAWNED] [%i]", logMessage, SDL_GetTicks());
			LogTime::write("MORE FROGS SPAWNED", SDL_GetTicks(), logMessage);
		}
	}
}
void Squares::Clean() 
{
	for (int i = 0; i < objects.size(); i++)
	{
		delete sprites[i];
		delete objects[i];
	}
	Mix_FreeChunk(GOOD_FROG);
	Mix_FreeChunk(BAD_FROG);
}
void Squares::setBorders(int x, int y) 
{
	wX = x;
	wY = y;
	for (int i = 0; i < objects.size(); i++) objects[i]->setBorders(x, y);
}
void Squares::setMix(bool m) 
{
	audio = m;
	if (m == false) 
	{
		Mix_VolumeChunk(GOOD_FROG, startVol);
		Mix_VolumeChunk(BAD_FROG, startVol);
	}
	else 
	{
		Mix_VolumeChunk(GOOD_FROG, 0);
		Mix_VolumeChunk(BAD_FROG, 0);
	}
}
void Squares::setMix(int vol) 
{
	if (startVol + vol > 128) return;
	if (startVol + vol < 0) return;
	Mix_VolumeChunk(GOOD_FROG, startVol + vol);
	Mix_VolumeChunk(BAD_FROG, startVol + vol);
}
bool Squares::getCollision() 
{
	return collision;
}
int Squares::scoreMultiplier(int score) 
{
	if (extraScore == 2) { SDL_Log("[%s] [PLAYER SCORE DOUBLED] [%i]", logMessage, SDL_GetTicks()); LogTime::write("PLAYER SCORE DOUBLED", SDL_GetTicks(), logMessage);}
	else if (extraScore == 0) { SDL_Log("[%s] [PLAYER SCORE NULLIFIED] [%i]", logMessage, SDL_GetTicks()); LogTime::write("PLAYER SCORE NULLIFIED", SDL_GetTicks(), logMessage);}
	collision = false;
	return score * extraScore;
}
void Squares::setFrogs(int frogs) 
{
	numb = frogs;
}
Squares::~Squares() {}

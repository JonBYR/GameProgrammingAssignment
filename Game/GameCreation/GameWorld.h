#pragma once
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
//#include "SDL_mixer.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Timer.h"
#include "Squares.h"
#include "SimpleSprite.h"
#include "LogTime.h"
#include <fstream>
#include <string>
class GameWorld
{
public:
	GameWorld();
	~GameWorld();
	void Init(const char* name, int x, int y, int width, int height, int flags);
	void virtual Render();
	void virtual Update();
	void virtual Input();
	void virtual Clean();
	bool getRunning();
	Uint32 TimerCallBackFunction(Uint32 interval, void* param);
	static Uint32 TimerCallBackFunctionCB(Uint32 interval, void* param);
	bool isKeyDown(SDL_Scancode key);
	void Splash();
	void End();
private:
	bool gameRun;
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
	std::vector<GameObject*> objects;
	Player* player;
	Timer timer;
	SimpleSprite* playerSprite;
	const int DELTA_TIME = 30;
	Squares sqr;
	int windowX;
	int windowY;
	int gameActive = 60;
	float elapsed;
	int score;
	char logMessage[32];
	TTF_Font* sans;
	SDL_Color white;
	SDL_Surface* surfaceMessage;
	SDL_Texture* textureMessage;
	SDL_Rect messageRect;
	const Uint8* keyState;
	bool fullscreen;
	bool splash;
	int fontSize;
	bool mute;
	bool frogCollected;
	//Mix_Music* backingMusic;
	int volume;
	bool timerExtended;
	std::ifstream frogs;
	int frogLevel[3];
	int number;
	bool sPressed;
	bool uPressed;
	bool dPressed;
};


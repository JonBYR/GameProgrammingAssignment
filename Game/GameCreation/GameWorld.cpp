#include "GameWorld.h"
GameWorld::GameWorld() {}
Uint32 GameWorld::TimerCallBackFunction(Uint32 interval, void* param)
{
	SDL_Event event;
	SDL_UserEvent userevent;
	userevent.type = SDL_USEREVENT;
	userevent.code = 5;
	userevent.data1 = (void*)"Timer Countdown";
	userevent.data2 = NULL;
	event.type = SDL_USEREVENT;
	event.user = userevent;
	SDL_PushEvent(&event);
	return(interval);
}
Uint32 GameWorld::TimerCallBackFunctionCB(Uint32 interval, void* param)
{
	return ((GameWorld*)param)->TimerCallBackFunction(interval, param);
}
bool GameWorld::isKeyDown(SDL_Scancode key) 
{
	if (keyState != 0)
	{
		if (keyState[key] == 1) return true;
		else return false;
	}
}
void GameWorld::Init(const char* name, int x, int y, int width, int height, int flags)
{
	SDL_AddTimer(1000, &TimerCallBackFunctionCB, NULL);
	gameWindow = SDL_CreateWindow(name, x, y, width, height, flags); //paramters passed in will create the game Window in the game world object (which can be inherited)
	gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED); //renderer created
	gameRun = true; //bool set to true
	player = new Player();
	playerSprite = new SimpleSprite(0, 0, 17, 18);
	player->Init(50, 200, 50, 50, 255, 0, 0);
	frogs.open("FrogLevel.txt");
	std::string frog;
	int i = 0;
	while (getline(frogs, frog))
	{
		frogLevel[i] = stoi(frog);
		i++;
	}
	sqr.Init(50, 0, 10.0, 10.0, frogLevel[0]);
	SDL_GetWindowSize(gameWindow, &windowX, &windowY);
	player->setBorders(windowX, windowY);
	sqr.setBorders(windowX, windowY);
	player->SetMix(false);
	sqr.setMix(false);
	gameActive = 60;
	playerSprite->load(gameRenderer, "content/spritesheet.png");
	LogTime::getTime(logMessage, 32);
	score = 0;
	sans = TTF_OpenFont("./content/OpenSans-Regular.ttf", 18);
	white = { 255, 255, 255 };
	messageRect.x = 0;
	messageRect.y = 0;
	messageRect.w = 100;
	messageRect.h = 100;
	volume = 32;
	fullscreen = false;
	splash = true;
	mute = false;
	timerExtended = false;
	/*if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		printf("Warning: Audio has not been found! \n");
		SDL_Quit();
	}
	else
	{
		backingMusic = Mix_LoadMUS("./content/Fluffing-a-Duck.mp3");
		Mix_VolumeMusic(volume);
		Mix_PlayMusic(backingMusic, -1);
	}*/
	number = 0;
	sPressed = false;
}
void GameWorld::Splash() 
{
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
	messageRect.w = 400;
	messageRect.h = 400;
	surfaceMessage = TTF_RenderText_Blended_Wrapped(sans, "Frog Collection \n Up, Down, Left and Right Arrows to move \n Space to jump \n Left Shift to Sprint \n Right Shift to Stop \n F for fullscreen/non-fullscreen in game \n M to mute/unmute game \n U and D to increase and decrease volume \n S to change number of frogs" , white, 200);
	textureMessage = SDL_CreateTextureFromSurface(gameRenderer, surfaceMessage);
	SDL_RenderCopy(gameRenderer, textureMessage, NULL, &messageRect);
	SDL_RenderPresent(gameRenderer);
	SDL_FreeSurface(surfaceMessage);
	SDL_Log("[%s] [SPLASH SCREEN LOADED] [%i]", logMessage, SDL_GetTicks());
	LogTime::write("SPLASH SCREEN LOADED", SDL_GetTicks(), logMessage);
	messageRect.w = 100;
	messageRect.h = 100;
	frogCollected = false;
	splash = false;
}
void GameWorld::Input()
{
	SDL_Event event;
	keyState = SDL_GetKeyboardState(0);
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: //if the x is pressed on the window the bool is set to false, breaking the while loop in main
			gameRun = false;
			SDL_Log("[%s] [GAME EXITED] [%i]", logMessage, SDL_GetTicks());
			LogTime::write("GAME EXITED", SDL_GetTicks(), logMessage);
			break; 
		case SDL_USEREVENT:
			if (splash == true) gameActive = 60;
			else 
			{
				gameActive--;
				frogCollected = sqr.getCollision();
				if (frogCollected == true)
				{
					score = sqr.scoreMultiplier(score);
					frogCollected = false;
				}
				else
				{
					if (gameActive <= 15) score = score + 2;
					else score++;
				}
				if (gameActive <= 0)
				{

					if ((score >= 100) && (timerExtended == false))
					{
						gameActive = gameActive + 15;
						SDL_Log("[%s] [GAME TIMER HAS EXTENDED] [%i]", logMessage, SDL_GetTicks());
						LogTime::write("GAME TIMER HAS EXTENDED", SDL_GetTicks(), logMessage);
						timerExtended = true;
					}
					else
					{
						gameRun = false;
						SDL_Log("[%s] [GAME TIMER HAS ENDED] [%i]", logMessage, SDL_GetTicks());
						LogTime::write("GAME TIMER HAS ENDED", SDL_GetTicks(), logMessage);
						break;
					}
			}
			}
		default: //prevents infinite loop in main
			break;
		}
	}
	player->Input();
	if (isKeyDown(SDL_SCANCODE_F)) 
	{
		fullscreen = !fullscreen;
		if (fullscreen == true) 
		{
			SDL_SetWindowFullscreen(gameWindow, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
			SDL_Log("[%s] [GAME HAS GONE FULLSCREEN] [%i]", logMessage, SDL_GetTicks());
			LogTime::write("GAME HAS GONE FULLSCREEN", SDL_GetTicks(), logMessage);
		}
		else 
		{
			SDL_SetWindowFullscreen(gameWindow, 0);
			SDL_Log("[%s] [GAME HAS GONE OUT OF FULLSCREEN] [%i]", logMessage, SDL_GetTicks());
			LogTime::write("GAME HAS GONE OUT OF FULLSCREEN", SDL_GetTicks(), logMessage);
		}
	}
	if (isKeyDown(SDL_SCANCODE_M)) 
	{
		if (mute == false) 
		{
			//Mix_PauseMusic();
			player->SetMix(true);
			sqr.setMix(true);
			mute = true;
			SDL_Log("[%s] [GAME HAS MUTED] [%i]", logMessage, SDL_GetTicks());
			LogTime::write("GAME HAS MUTED", SDL_GetTicks(), logMessage);
		}
		else 
		{
			//Mix_ResumeMusic();
			player->SetMix(false);
			sqr.setMix(false);
			mute = false;
			SDL_Log("[%s] [GAME HAS UNMUTED] [%i]", logMessage, SDL_GetTicks());
			LogTime::write("GAME HAS UNMUTED", SDL_GetTicks(), logMessage);
		}
	}
	if (isKeyDown(SDL_SCANCODE_D) && !dPressed) 
	{
		uPressed = true;
		volume = volume - 10;
		//Mix_VolumeMusic(volume);
		//Mix_Volume(-1, volume);
		player->SetMix(-10);
		sqr.setMix(-10);
		SDL_Log("[%s] [GAME VOLUME DECREASED] [%i]", logMessage, SDL_GetTicks());
		LogTime::write("GAME VOLUME DECREASED", SDL_GetTicks(), logMessage);
	}
	if (isKeyDown(SDL_SCANCODE_U) && !uPressed) 
	{
		dPressed = true;
		volume = volume + 10;
		//Mix_VolumeMusic(volume);
		//Mix_Volume(-1, volume);
		player->SetMix(10);
		sqr.setMix(10);
		SDL_Log("[%s] [GAME VOLUME INCREASED] [%i]", logMessage, SDL_GetTicks());
		LogTime::write("GAME VOLUME INCREASED", SDL_GetTicks(), logMessage);
	}
	if (isKeyDown(SDL_SCANCODE_S) && !sPressed) 
	{
		sPressed = true;
		if (number == 3) 
		{ 
			sqr.setFrogs(frogLevel[0]);
			number = 0;
			SDL_Log("[%s] [FROG LEVEL RESET] [%i]", logMessage, SDL_GetTicks());
			LogTime::write("FROG LEVEL RESET", SDL_GetTicks(), logMessage);
		}
		else 
		{
			sqr.setFrogs(frogLevel[number + 1]);
			number++;
			SDL_Log("[%s] [FROG LEVEL INCREASED] [%i]", logMessage, SDL_GetTicks());
			LogTime::write("FROG LEVEL INCREASED", SDL_GetTicks(), logMessage);
		}
	}
	else 
	{
		sPressed = false;
		dPressed = false;
		uPressed = false;
	}
}
void GameWorld::Update()
{
	timer.resetTicksTimer();
	player->Update();
	playerSprite->update(0);
	SDL_Rect playerRect = player->getRect();
	sqr.Update(&playerRect);
	if (timer.getTicks() < DELTA_TIME)
	{
		SDL_Delay(DELTA_TIME - timer.getTicks());
	}
	if (elapsed >= 60) gameRun = false;
}
void GameWorld::Render()
{
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
	SDL_RenderClear(gameRenderer);
	playerSprite->render(gameRenderer, player->getRect(), player->getFlip());
	SDL_Log("[%s] [PLAYER RENDER] [%i]", logMessage, SDL_GetTicks());
	LogTime::write("PLAYER RENDER", SDL_GetTicks(), logMessage);
	sqr.Render(gameRenderer);
	surfaceMessage = TTF_RenderText_Solid(sans, (std::to_string(score)).c_str(), white);
	textureMessage = SDL_CreateTextureFromSurface(gameRenderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);
	SDL_RenderCopy(gameRenderer, textureMessage, NULL, &messageRect);
	SDL_RenderPresent(gameRenderer);
}
void GameWorld::End() 
{
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
	messageRect.x = 100;
	messageRect.y = 200;
	messageRect.w = 200;
	messageRect.h = 200;
	surfaceMessage = TTF_RenderText_Blended_Wrapped(sans, "Game Over!", white, 100);
	textureMessage = SDL_CreateTextureFromSurface(gameRenderer, surfaceMessage);
	SDL_RenderCopy(gameRenderer, textureMessage, NULL, &messageRect);
	SDL_RenderPresent(gameRenderer);
	SDL_FreeSurface(surfaceMessage);
	SDL_Log("[%s] [END SCREEN LOADED] [%i]", logMessage, SDL_GetTicks());
	LogTime::write("END SCREEN LOADED", SDL_GetTicks(), logMessage);
}
void GameWorld::Clean()
{
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(gameRenderer);
	player->Clean();
	//Mix_CloseAudio();
	IMG_Quit();
	SDL_Quit();
	delete player;
	delete playerSprite;
	sqr.Clean();
	LogTime::close();
}
bool GameWorld::getRunning()
{
	return gameRun;
}

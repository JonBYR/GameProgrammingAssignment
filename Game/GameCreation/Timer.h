#pragma once
#include "SDL.h"
class Timer
{
public:
	Timer();
	void resetTicksTimer();
	int getTicks();
private:
	int startTicks;
};


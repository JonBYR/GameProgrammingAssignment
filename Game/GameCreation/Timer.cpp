#include "Timer.h"
Timer::Timer()
{
	startTicks = 0;
}
void Timer::resetTicksTimer()
{
	startTicks = SDL_GetTicks(); //gets the number of milliseconds since program started
}
int Timer::getTicks()
{
	return (SDL_GetTicks() - startTicks); //return current - startTime
}
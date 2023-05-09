#pragma once
#include "SDL.h"
#include <iostream>

// "Simple" sprite class example outline - You need to complete the functions to make this work. This is intended to get you started, but needs a lot of
// work to make it fit for purpose. Get this working and then expand on it to make a proper sprite class for yourself.
// See the .cpp file for comments on what each function does
class SimpleSprite
{
public:
	SimpleSprite(int x, int y, int widthPixels, int heightPixels);
	SimpleSprite(int x, int y, int widthPixels, int heightPixels, int num);
	~SimpleSprite();

	// you might need to rename these functions to work with your own code.. don't forget to update the CPP file too!
	void render(SDL_Renderer * renderer, SDL_Rect distRec, bool flip);
	void update(int ticks);
	void load(SDL_Renderer * renderer, const char * path, bool bUseColourKey = false);
	void setNumberOfFrames(unsigned int framecount);
	void setAnimationSpeed(unsigned int speed);

	// x and y position of the sprite in screen space
	int x, y = 0;
	// width and height of the sprite within the source texture
	int frameWidthPixels, frameHeightPixels = 0;
	// optional, scale the destination sprite during rendering
	int xscale, yscale = 1;
	int getNumber();
protected:
	SDL_Texture * texture = nullptr;	// pointer to an SDL_Texture, always initialize your pointers to either NULL or nullptr
	SDL_Rect srcRect;					// this is the source rectangle where we will copy the sprite from within the texture

	unsigned int numberOfFrames = 4;	// how many frames of animation?
	unsigned int animationSpeed = 200;	// how many milliseconds between each frame of animation?
	unsigned int frameIndex = 0;		// which frame are we currently on?
	int number;
};


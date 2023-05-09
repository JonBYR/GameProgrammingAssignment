//#include "stdafx.h"
#include "SimpleSprite.h"
#include "SDL_Image.h"	// we need this for texture loading function

// default constructor isn't needed as all member variables are given default values already

// constructor that takes X,Y position and width/height values for sprite (src Rect will be calculated from them based on current frame)
// X is the starting X position, Y is the starting Y position to draw on screen. Width and Height are the size of a single frame of the sprite
// todo: think if we need to add more data here? Should we have scale? Should we have an offset value?? (so the sprite is centered at X,Y)
SimpleSprite::SimpleSprite(int x, int y, int widthPixels, int heightPixels)
{
	frameWidthPixels = widthPixels;
	frameHeightPixels = heightPixels;
	frameIndex = 0;
	srcRect.x = frameIndex * frameWidthPixels;
	srcRect.y = 0;
	srcRect.w = frameWidthPixels;
	srcRect.h = frameHeightPixels;
}
SimpleSprite::SimpleSprite(int x, int y, int widthPixels, int heightPixels, int num)
{
	frameWidthPixels = widthPixels;
	frameHeightPixels = heightPixels;
	frameIndex = 0;
	srcRect.x = frameIndex * frameWidthPixels;
	srcRect.y = 0;
	srcRect.w = frameWidthPixels;
	srcRect.h = frameHeightPixels;
	number = num;
}
// here you should safely handle any memory you allocated.. remember you are loading textures? Do they need cleaning up?
SimpleSprite::~SimpleSprite()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}
}

// render the sprite to the current renderer using the current X,Y positions based on the current FrameIndex we are at
// usually you'd calculate your X,Y and scaled width and height in update, here you'd use the SDL_Rect values you've calculated
// to call SDL_RenderCopy to actually do the rendering. See slides for info.
void SimpleSprite::render(SDL_Renderer * renderer, SDL_Rect distRec, bool flip)
{
	srcRect.x = (frameWidthPixels * frameIndex);
	if (flip == true) SDL_RenderCopyEx(renderer, texture, &srcRect, &distRec, 0, 0, SDL_FLIP_HORIZONTAL);
	else if (flip == false) SDL_RenderCopyEx(renderer, texture, &srcRect, &distRec, 0, 0, SDL_FLIP_NONE);
}

// this function should handle the logic of choosing the "source rectangle" srcRect, easy version is to follow the modulo % math given in the slides
// but that results in only playing a single sequence. Far better to expand on this and create your own sprite class!
void SimpleSprite::update(int ticks)
{
	unsigned int ticker = SDL_GetTicks();
	frameIndex = (ticker / animationSpeed) % numberOfFrames;
}
// load the texture (see lecture slides), colour key is usually not required for PNG with alpha channel (RGBA images)
// the "colour key" is essentially the first pixel (top left of the image) and is considered transparent when we don't have alpha channels (RGB images)
// its a bit old school, but some sprite sheets come with no alpha, so this is the convention to draw them properly
// note we need to pass the current SDL Renderer pointer into this function so that image functions work correctly for texture creation
// Note: In the case of using a colour key, we will likely want to use IMG_Load and store a temporary SDL_Surface * so we can then use SDL_SetColorKey on that
// surface before calling SDL_CreateTextureFromSurface
// If we don't need colour keying, we can simply call IMG_LoadTexture
void SimpleSprite::load(SDL_Renderer * renderer,const char * path, bool bUseColourKey)
{
	texture = IMG_LoadTexture(renderer, path);
}

// simple setter
void SimpleSprite::setNumberOfFrames(unsigned int framecount)
{
	numberOfFrames = framecount;
}
// simple setter
void SimpleSprite::setAnimationSpeed(unsigned int speed)
{
	animationSpeed = speed;
}
int SimpleSprite::getNumber() 
{
	return number;
}

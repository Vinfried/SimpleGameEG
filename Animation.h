#pragma once

#include "SDL.h"
#include "Texture.h"

class Animation
{
public:

	Animation();

	Animation(Texture* inSpriteSheet, int inNumberOffFrames = 1, 
		float inFrameDuration = 0.1f, int inStartFrame = 0, int inEndFrame = 0 );

	~Animation();

	//update the animation on each frame
	void update(float deltaTime);

	//draw the texture to the screen at the positions
	void draw(SDL_Renderer* renderer, Vector2 pos, int scale = 1, bool flip = false);

	int getFrameWidth() { return frameWidth; };

	int getFrameHeight() { return frameHeight; };

private:

	//start and end frame
	unsigned int startFrame;
	unsigned int endFrame;

	//frame width and height
	unsigned int frameWidth;
	unsigned int frameHeight;

	//texture image for the sprite
	Texture* spriteSheet;

	//timer since the last sprite update
	float frameTimer;

	//how long each frame should hold for
	float frameDuration;

	//what frame are we currently showing
	unsigned int currentFrame;
};


#include <iostream>
#include "Animation.h"

using namespace std;

Animation::Animation()
{
}

Animation::Animation(Texture* inSpriteSheet, int inNumberOfFrames,
	float inFrameDuration, int inStartFrame, int inEndFrame)
{
	//set default values
	spriteSheet = inSpriteSheet;
	startFrame = inStartFrame;
	endFrame = inEndFrame;
	frameDuration = inFrameDuration;
	frameTimer = 0.0f;
	currentFrame = startFrame;

	if (spriteSheet != nullptr) {
		frameWidth = spriteSheet->getImageWidth() / SDL_max(1, inNumberOfFrames);
		frameHeight = spriteSheet->getImageHeight();
	}
}

Animation::~Animation()
{
	if (spriteSheet != nullptr) {
		//deallocate the sprite sheet object
		delete spriteSheet;
		spriteSheet = nullptr;
	}
	else {
		cout << "Error - No texture found in animation." << endl;
	}
}

void Animation::update(float deltaTime)
{
	//update the timer each frame
	frameTimer += deltaTime;

	//if the frame timer has passed the frame duration
	if (frameTimer >= frameDuration) {
		currentFrame++;

		frameTimer = 0.0f;

		if (currentFrame >= endFrame) {
			currentFrame = startFrame;
		}
	}
}

void Animation::draw(SDL_Renderer* renderer, Vector2 pos, int scale, bool flip)
{
	

	//get the current rendering frame clipping region
	SDL_Rect clip;
	clip.x = currentFrame * frameWidth;
	clip.y = 0;
	clip.w = frameWidth;
	clip.h = frameHeight;

	//draw to the screen
	spriteSheet->draw(renderer, pos, &clip, scale, flip);
}

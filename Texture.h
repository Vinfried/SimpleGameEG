#pragma once

#include <SDL.h>
#include "Vector2.h"

class Texture
{
public:
	Texture();
	~Texture();

private:
	//hold reference to the text file
	SDL_Texture* sdlTexture;

	//set dimentions for the file
	int width;
	int height;

public:
	//load the image for path
	//add the texture to the renderer
	bool loadImageFromFile(const char* path, SDL_Renderer* renderer);

	//render the image to the screen when called
	//param 1 - to copy the text to the renderer
	//param 2 & 3 - x and y position of the texture on the screen
	//param 4 - the area we want to copy from the texture onto the window
	void draw(SDL_Renderer* renderer, Vector2 pos, SDL_Rect* sourceRect = NULL, int scale = 1, bool flip = false);

	//return the dimensions of the image
	int getImageWidth() { return width; }
	int getImageHeight() { return height; }

	//remove the texture from memory
	void resetTexture();
};


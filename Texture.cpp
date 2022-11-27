#include <iostream>
#include "Texture.h"
#include "SDL_image.h"

using namespace std;

Texture::Texture()
{
	//set default texture to nullptr
	sdlTexture = nullptr;
	//set the width and height to 0
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	resetTexture();
}

bool Texture::loadImageFromFile(const char* path, SDL_Renderer* renderer)
{
	if (sdlTexture == nullptr) {
		//Load the image to the surface
		SDL_Surface* loadSurface = IMG_Load(path);

		if (loadSurface != nullptr) {
			cout << "Load Texture - success" << endl;

			//create the texture from the surface
			sdlTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);

			if (sdlTexture != nullptr) {
				cout << "Create texture from surface - success" << endl;

				//get the dimensions of the image
				width = loadSurface->w;
				height = loadSurface->h;
			}
			else {
				cout << "Create texture from surface - failed" << endl;
			}

			SDL_FreeSurface(loadSurface);
		}
		else {
			cout << "Load Texture - failed" << SDL_GetError() << endl;
		}
	}
	else {
		cout << "Remove the existing texture before loading..." << endl;
		
		return false;
	}
	//id sdlTexture != nullptr return true, otherwise false
	return sdlTexture != nullptr;
}

void Texture::draw(SDL_Renderer* renderer, Vector2 pos, SDL_Rect* sourceRect, int scale, bool flip)
{
	SDL_Rect destinationRect = {pos.x, pos.y, width, height };

	//clip/crop img if we have source rect
	if (sourceRect != nullptr) {
		destinationRect.w = sourceRect->w * scale;
		destinationRect.h = sourceRect->h * scale;
	}

	SDL_RendererFlip flipflag = SDL_FLIP_NONE;

	if (flip) {
		flipflag = SDL_FLIP_HORIZONTAL;
	}

	//render to the screen
	SDL_RenderCopyEx(renderer, sdlTexture, sourceRect, &destinationRect, 0, 0, flipflag);
}

void Texture::resetTexture()
{
	//deallocate texture
	if (sdlTexture != nullptr) {
		SDL_DestroyTexture(sdlTexture);
		sdlTexture = nullptr;
		width = 0;
		height = 0;
	}
}

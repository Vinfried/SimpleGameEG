#include "Collectible.h"
#include "SDL.h"
#include <iostream>
#include "Vector2.h"

Collectible::Collectible(Texture* collectibleTexture, Vector2 pos, int numberOfFrames)
{
	position = pos;
	objectCenter = pos;
	objectTexture = collectibleTexture;
	this->numberOfFrames = numberOfFrames;
	float w = 10.0f;
	float h = 10.0f;

	//if we have a texture then update the width and height based on the texture
	if (objectTexture != nullptr) {
		w = objectTexture->getImageWidth() / SDL_max(1, numberOfFrames);
		h = objectTexture->getImageHeight();

		w /= 2;
		h /= 2;
	}
	setCollision(objectCenter, Vector2(w, h));
}

Collectible::~Collectible()
{
}

void Collectible::draw(SDL_Renderer* renderer)
{
	SDL_Rect clip;
	clip.x = 0;
	clip.y = 0;
	clip.h = objectTexture->getImageHeight();
	clip.w = objectTexture->getImageWidth() / SDL_max(1, numberOfFrames);

	objectTexture->draw(renderer, position, &clip);
}

void Collectible::update(float deltaTime)
{
	GameObject::update(deltaTime);
}

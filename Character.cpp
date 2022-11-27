#include "Character.h"
#include "SDL.h"
#include <iostream>
#include "Vector2.h"

using namespace std;

Character::Character(Texture* characterTexture, Vector2 pos, int numberOfFrames)
{
	position = pos;
	objectCenter = position;
	objectTexture = characterTexture;
	this->numberOfFrames = numberOfFrames;
	velocity = Vector2().zero();
	movementAxis = Vector2().zero();
	maxSpeed = 100.0f;
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

void Character::draw(SDL_Renderer* renderer)
{
	GameObject::draw(renderer);

	SDL_Rect clip;
	clip.x = 0;
	clip.y = 0;
	clip.h = objectTexture->getImageHeight();
	clip.w = objectTexture->getImageWidth() / SDL_max(1, numberOfFrames);

	objectTexture->draw(renderer, position, &clip);


}

void Character::update(float deltaTime)
{
	//this will make sure the gameobject update code runs first
	GameObject::update(deltaTime);
	//set the velocity to be our movement axis normalised * our speed
	velocity = movementAxis * maxSpeed;
	//move the character based on velocity
	position += velocity * deltaTime;
}

void Character::setMovementAxis(Vector2 axis)
{
	movementAxis = axis;
}

Vector2 Character::getMovementAxis()
{
	return movementAxis;
}



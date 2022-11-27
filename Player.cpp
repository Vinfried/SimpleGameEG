#include "Player.h"
#include "SDL.h"

Player::Player(Texture* characterTexture, Vector2 pos, int numberOfFrames)
	:Character::Character(characterTexture, pos, numberOfFrames)
{
	tag = "Player";
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{
	Character::update(deltaTime);
}

void Player::processInput(Input* userInput)
{
	float movementX = 0.0f;
	float movementY = 0.0f;

	if (userInput->isKeyDown(SDL_SCANCODE_W)) {
		movementY = -1.0f;
	}

	if (userInput->isKeyDown(SDL_SCANCODE_S)) {
		movementY = 1.0f;
	}

	if (userInput->isKeyDown(SDL_SCANCODE_A)) {
		movementX = -1.0f;
	}
	
	if (userInput->isKeyDown(SDL_SCANCODE_D)) {
		movementX = 1.0f;
	}

	//store the colliders overlapping our collider
	vector<Collider*> otherColliders = getCollisions()[0]->getOverlappingColliders();

	if (userInput->isKeyDown(SDL_SCANCODE_SPACE)) {
		
		//run through all the colliders we're overlapping
		for (unsigned int i = 0; i < otherColliders.size(); ++i) {
			if (otherColliders[i]->getOwner()->tag == "Enemy") {
				SDL_Log("Collider detected, Enemy: Ouch!");
				otherColliders[i]->getOwner()->destroyGameObject();
			}
			
		}
	}

	//this will run through all the colliders overlapping each frame
	for (vector<Collider*>::iterator it = otherColliders.begin(); it < otherColliders.end(); ++it) {
		if ((*it)->getOwner()->tag == "Orb") {
			SDL_Log("Orb collected");
			(*it)->getOwner()->destroyGameObject();
		}
	}

	setMovementAxis(Vector2(movementX, movementY));
}

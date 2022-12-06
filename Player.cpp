#include "Player.h"
#include "SDL.h"

Player::Player(Texture* characterTexture, Vector2 pos, int numberOfFrames)
	:Character::Character(characterTexture, pos, numberOfFrames)
{
	tag = "Player";
	animationStates = playerStates::idle;
}

Player::~Player()
{
}

void Player::draw(SDL_Renderer* renderer)
{
	GameObject::draw(renderer);

	Animation* playerAnimation = nullptr;

	switch (animationStates) {
	case playerStates::idle:
		playerAnimation = playerAnims.idle;
		break;
	
	case playerStates::run:
		playerAnimation = playerAnims.run;
		break;
	
	case playerStates::attack:
		playerAnimation = playerAnims.attack;
		break;

	case playerStates::die:
		playerAnimation = playerAnims.die;
		break;

	case playerStates::jump:
		playerAnimation = playerAnims.jump;
		break;
	}

	if (!flip) {
		playerAnimation->draw(renderer, position);
	}
	else {
		playerAnimation->draw(renderer, position,1 , flip = true);
	}
	
}

void Player::update(float deltaTime)
{
	Character::update(deltaTime);
	
	if (velocity.length() > 0) {
		animationStates = playerStates::run;
	}
	else {
		animationStates = playerStates::idle;
	}

	if (attack) {
		animationStates = playerStates::attack;
		attack = false;
	}
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
		flip = true;
	}
	
	if (userInput->isKeyDown(SDL_SCANCODE_D)) {
		movementX = 1.0f;
		flip = false;
	}

	//store the colliders overlapping our collider
	vector<Collider*> otherColliders = getCollisions()[0]->getOverlappingColliders();

	if (userInput->isKeyDown(SDL_SCANCODE_SPACE)) {
		
		attack = true;

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

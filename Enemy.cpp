#include "Enemy.h"

Enemy::Enemy(Texture* characterTexture, Vector2 pos, int numberOfFrames)
:Character::Character(characterTexture, pos, numberOfFrames)
{
	maxSpeed = 25.0f;
	tag = "Enemy";
}

Enemy::~Enemy()
{
}

void Enemy::update(float deltaTime)
{
	Character::update(deltaTime);

	setMovementAxis(Vector2(1.0f, 0.0f));
}

void Enemy::processInput(Input* userInput)
{
}



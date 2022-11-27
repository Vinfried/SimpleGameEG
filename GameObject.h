#pragma once

#include <string>
#include"SDL.h"
#include "Texture.h"
#include "Vector2.h"
#include "Input.h"
#include "Collider.h"

using namespace std;

class GameObject
{
public:
	GameObject();
	~GameObject();

	//this will be the true update that states should run
	void updateGameObject(float deltaTime, vector<GameObject*>& gameObjectStack);

	virtual void draw(SDL_Renderer* renderer);
	virtual void processInput(Input* userInput) {}

	//this is going to create a collision for the game object
	void setCollision(Vector2 position, Vector2 halfDimentions, bool shouldDebug = true);

	//this will change the width and height of the collider
	void setCollisionDimentions(Collider* collision, Vector2 halfDimentions);

	//this will move the position of the collision based on the objects center
	void updateCollisionPositions();
	void findObjectCenter();

	//Get the collision publicly
	vector<Collider*> getCollisions();

	//return if this should be deleted
	bool shouldDelete() const;
	
	//set the game object to be destroyed
	void  destroyGameObject();

	//this will be an identifier for anything that needs to know specifics
	string tag;

	//get hte game position
	Vector2 getPosition() { return objectCenter; }

protected:
	virtual void update(float deltaTime) {}
	//position for the game object to display
	Vector2 position;
	//the objects texture
	Texture* objectTexture;
	//Collider
	vector<Collider*> collisions;
	//get the center of the object
	Vector2 objectCenter;
	//number of frames in the object texture
	unsigned int numberOfFrames;

private:

	//this will define whether or not the gameobject should be deleted
	bool bShouldDelete;
};


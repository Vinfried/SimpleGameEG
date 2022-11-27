#pragma once

#include <vector>
#include "SDL.h"
#include "Vector2.h"

using namespace std;

//when two classes both need data from each other it creates a chicken and egg paradox(resulting in an infinite loop)
//we can use forward declaration to solve this paradox, instead of adding an #include
class GameObject;

class Collider
{
public:
	Collider(GameObject* ownerObject, Vector2 position = Vector2().zero(), Vector2 halfDimentions = Vector2(1.0f, 1.0f), bool shouldDebug = true);
	~Collider();

	//we need to detect if we are colliding with any of the other colliders in the game
	void update(float deltaTime, vector<Collider*>& otherColliders);
	void draw(SDL_Renderer* renderer);

	//set bounds for the collider
	SDL_FRect colliderRect;

	//get the other colliders that are overlapping this collider
	vector<Collider*> getOverlappingColliders() const;

	//debug to draw the collider to the screen
	bool bDebug;

	GameObject* getOwner() const;

protected:
	//store all the colliders that are overlapping this collider
	vector<Collider*> overlappedColliders;

	GameObject* ownerObject;
};


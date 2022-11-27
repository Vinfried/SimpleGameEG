#include "Collider.h"
#include <vector>

using namespace std;

Collider::Collider(GameObject* ownerObject, Vector2 position, Vector2 halfDimentions, bool shouldDebug)
{
	bDebug = shouldDebug;
	overlappedColliders = {};
	this->ownerObject = ownerObject;

	float x = position.x - halfDimentions.x;
	float y = position.y - halfDimentions.y;
	float w = halfDimentions.x * 2;
	float h = halfDimentions.y * 2;

	//set the bounds based on the above algorithms
	colliderRect = { x, y, w, h };
}

Collider::~Collider()
{
	//looping through all of the colliders is overlapped with 
	for (vector<Collider*>::iterator col = overlappedColliders.begin(); col < overlappedColliders.end(); ++col) {
		//make sure the collider is in the other collider overlapped
		vector<Collider*>::iterator fCol = find((*col)->overlappedColliders.begin(), (*col)->overlappedColliders.end(), this);
		//if it's found then remove it from the colliders overlap
		if (fCol < (*col)->overlappedColliders.end()) {
			(*col)->overlappedColliders.erase(fCol);
		}
	}
}

void Collider::update(float deltaTime, vector<Collider*>& otherColliders)
{
	//chcke if this collider is intersecting with other colliders in the game
	for (unsigned int i = 0; i < otherColliders.size(); ++i) {
		//make sure othercollider isn't our collider
		if (otherColliders[i] != this) {
			//detect if this collider is intersecting with any other colliders
			//SDL_HasIntersection will be true if the colliders intersect or false if they don't
			if (SDL_HasIntersectionF(&colliderRect, &otherColliders[i]->colliderRect)) {
				//looking through the overlapped colliders array to detect if this collider is in there
				//this will pass an iteration number less than the end() if it's in the array
				vector<Collider*>::iterator it = find(overlappedColliders.begin(), overlappedColliders.end(), otherColliders[i]);
				if (it == overlappedColliders.end()) {
					overlappedColliders.push_back(otherColliders[i]);
					SDL_Log("Entered Collider");
				}
			}
			else {
				//check if the other collider is in the overlapped array
				vector<Collider*>::iterator it = find(overlappedColliders.begin(), overlappedColliders.end(), otherColliders[i]);
				//if it is then remove it from the array
				if (it < overlappedColliders.end()) {
					overlappedColliders.erase(it);
					//SDL_Log("Exited Collider");
				}
			}
		}
	}
}

void Collider::draw(SDL_Renderer* renderer)
{
	if(bDebug == true) {
		//is the overlapped colliders empty?
		if (overlappedColliders.empty()) {
			//set sdl draw colour to red
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);
		}
		else {
			//set sdl draw colour to green
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 1);
		}

		//draw the red colour as a rectangle based on our collider dimentions
		SDL_RenderDrawRectF(renderer, &colliderRect);

	}
}

vector<Collider*> Collider::getOverlappingColliders() const
{

	return overlappedColliders;
}

GameObject* Collider::getOwner() const
{
	return ownerObject;
}

#include "GameObject.h"
#include "Vector2.h"
#include "SDL.h"

GameObject::GameObject()
{
	position = Vector2().zero();
	objectTexture = nullptr;
	objectCenter = position;
	numberOfFrames = 1;
	bShouldDelete = false;
	tag = "";
}

GameObject::~GameObject()
{
	//remove the collision from memory if the there is one
	for (vector<Collider*>::iterator col = collisions.begin(); col < collisions.end(); ++col) {
		delete* col;
	}

	//shrink the array to a 0 size vector
	vector<Collider*>().swap(collisions);

	//remove the texture from memory if there is one
	if (objectTexture != nullptr) {
		delete objectTexture;
		objectTexture = nullptr;
	}
}

void GameObject::updateGameObject(float deltaTime, vector<GameObject*>& gameObjectStack)
{
	//this will find the object center based on the textuure if there is one
	findObjectCenter();
	//this will update the collision position to match the object center
	updateCollisionPositions();

	//create a termporary vector of all the colliders
	vector<Collider*> otherCollider = {};

	//search through all the game objects to get their colliders
	for (vector<GameObject*>::iterator go = gameObjectStack.begin(); go < gameObjectStack.end(); ++go) {
		//point to the vector of colliders in each gameobject
		vector<Collider*> goColliders = (*go)->getCollisions();
		//loop through the gameobject colliders and add them each into the otherColliders vector
		for (vector<Collider*>::iterator col = goColliders.begin(); col < goColliders.end(); ++col) {
			//add the collider to the vector
			otherCollider.push_back(*col);
		}
	}

	//hand the collision detection for our colliders
	for (vector<Collider*>::iterator col = otherCollider.begin(); col < otherCollider.end(); ++col) {
		(*col)->update(deltaTime, otherCollider);
	}

	//run the derived update
	update(deltaTime);

}

void GameObject::draw(SDL_Renderer* renderer)
{
	//check through the colliders if we have any
	for (vector<Collider*>::iterator col = collisions.begin(); col < collisions.end(); ++col) {
		//run the draw if they habe debug set
		if ((*col)->bDebug) {
			(*col)->draw(renderer);
		}
	}
}

void GameObject::setCollision(Vector2 position, Vector2 halfDimentions, bool shouldDebug)
{
	//define the gameobjects collision
	Collider* newCollision = new Collider(this, position, halfDimentions,shouldDebug);
	//add the collider to the collision vector
	collisions.push_back(newCollision);
}

void GameObject::setCollisionDimentions(Collider* collision,Vector2 halfDimentions)
{
	if (collision != nullptr) {
		//set the width of the collider
		collision->colliderRect.w = halfDimentions.x * 2;
		//set the height of the collider
		collision->colliderRect.h = halfDimentions.y * 2;
	}
}

void GameObject::updateCollisionPositions()
{
	//check if there is even a collision
	for (vector<Collider*>::iterator col = collisions.begin(); col < collisions.end(); ++col) {
		float w = (*col)->colliderRect.w / 2;
		float h = (*col)->colliderRect.h / 2;

		//change the position of the collider equal to the object center
		//center the collider based on it's half dimention
		(*col)->colliderRect.x = objectCenter.x - w;
		(*col)->colliderRect.y = objectCenter.y - h;
	}
}

void GameObject::findObjectCenter()
{
	//make sure we set back to the position each frame
	objectCenter = position;

	if (objectTexture != nullptr) {
		float w = objectTexture->getImageWidth() / SDL_max(1, numberOfFrames);
		float h = objectTexture->getImageHeight();

		w /= 2;
		h /= 2;

		objectCenter.x += w;
		objectCenter.y += h;
	}
}

vector<Collider*> GameObject::getCollisions()
{
	//return a vector of collisions
	return collisions;
}

bool GameObject::shouldDelete() const
{
	//this will be the key that tells the game this needs to be deleted
	return bShouldDelete;
}

void GameObject::destroyGameObject()
{
	//set should delete
	bShouldDelete = true;
}

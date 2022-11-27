#include "GameState.h"

GameState::GameState()
{
	stateID = 0;
	defaultBackgroundColour = { 15, 15, 255, 15 };
}

GameState::~GameState()
{
	//deallocate all of the game objects in the state
	for (vector<GameObject*>::iterator go = gameObjectStack.begin(); go < gameObjectStack.end(); go++) {
		delete* go;
	}

	//clear the vector
	vector<GameObject*>().swap(gameObjectStack);
}

void GameState::update(float deltaTime)
{
	//loop through all of the gameobjects and run their update
	for (vector<GameObject*>::iterator go = gameObjectStack.begin(); go < gameObjectStack.end(); go++) {
		(*go)->updateGameObject(deltaTime, gameObjectStack);
	}
}

void GameState::draw(SDL_Renderer* renderer)
{
	//Draw background colour as blue
	SDL_SetRenderDrawColor(renderer, defaultBackgroundColour.r, defaultBackgroundColour.g, defaultBackgroundColour.b, defaultBackgroundColour.a);
	SDL_RenderClear(renderer);

	//loop through all of the gameobjects and run their draw
	for (vector<GameObject*>::iterator go = gameObjectStack.begin(); go < gameObjectStack.end(); go++) {
		(*go)->draw(renderer);
	}
}

void GameState::processInput(Input* userInput)
{
	//loop through all of the gameobjects and run their processInput
	for (vector<GameObject*>::iterator go = gameObjectStack.begin(); go < gameObjectStack.end(); go++) {
		(*go)->processInput(userInput);
	}
}

void GameState::handleGarbage()
{
	//loop through all the gameObjects and handle their garbage
	for (vector<GameObject*>::iterator go = gameObjectStack.begin(); go < gameObjectStack.end();) {
		//check if they're marked for delete
		if ((*go)->shouldDelete()) {
			//deallocate it from memory
			delete* go;

			go = gameObjectStack.erase(go);
		}
		else {
			//increment the iterator if we didn't delete anything
			go++;
		}
	}
}

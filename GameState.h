#pragma once

#include "SDL.h"
#include "Input.h"
#include "GameObject.h"

class GameState
{
public:
	GameState();
	~GameState();

	//the game states version of all of the loop functions
	virtual void update(float deltaTime);
	virtual void draw(SDL_Renderer* renderer);
	virtual void processInput(Input* userInput);
	virtual void handleGarbage();

	//will be called when the game state begins and ends
	virtual bool onEnter(SDL_Renderer* renderer, SDL_Window* window) { return true; }
	virtual bool onExit() { return true; }

	//way to identify the state
	Uint32 stateID;

	//the default background colour of the state
	SDL_Colour defaultBackgroundColour;

protected:
	//this will store all the game objects in the state
	vector<GameObject*> gameObjectStack;

};


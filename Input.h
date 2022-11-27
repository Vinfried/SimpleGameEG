#pragma once
#include "SDL.h"
#include <vector>

using namespace std;

//forward declare game to avoid circular dependencies
class Game;

class Input
{
public:
	Input(Game* myGame);
	~Input();

	void updateInput(bool& bIsGameOver, vector<SDL_Window*> sdlWindows);

	//detect if a particular key is up or down
	bool isKeyDown(SDL_Scancode key);
	bool isKeyUp(SDL_Scancode key);

protected:
	void handleMenuEvents(SDL_Event* aEvent, vector<SDL_Window*> sdlWindows, bool &bIsGameOver);

private:
	//store the state of each key
	const Uint8* keyboardState;
	
	//store game class
	Game* myGame;
};


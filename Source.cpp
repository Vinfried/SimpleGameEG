#include <iostream>
#include "Game.h"

using namespace std;

int main(int argc, char** argv) {
	
	//create the game class and allocate to memory
	Game* newGame = new Game();

	//run the game
	newGame->Run("SimpleGameEG", 1200, 720, false);

	//dealocate the game object
	delete newGame;

	return 0;
}
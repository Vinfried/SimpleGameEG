#include <iostream>
#include <vector>
#include <Windows.h>
#include "Game.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Collectible.h"
#include "Orbs.h"
#include "Input.h"
#include "Collider.h"
#include "resource.h"
#include "SDL_syswm.h"
#include "RectangleObject.h"
#include <math.h>
#include "PlayState.h"
#include "MenuState.h"
#include "SDL_mixer.h"

using namespace std;

//constructor
Game::Game()
{
	//set the SDL Window and Renderer to null in case it has memory
	sdlWindow = {nullptr, nullptr};
	sdlRenderer = {nullptr, nullptr};
	//enemyTexture = nullptr;
	lastUpdatedTime = 0.0f;
	//playerTexture = nullptr;
	//orbsTexture = nullptr;
	userInput = nullptr;

	//Initialise the subsystem in the SDL2 Framework
	if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) != 0) {

		bIsGameOver = true;
		//if failed to initialise the subsystem, tell us on console
		cout << "Initialise SDL - failed" << endl;
	}
	else {
		//initialise font library
		if (TTF_Init() == -1) {
			//if the font subsystem fails
			bIsGameOver = true;

			SDL_Log("Font subsystem - Failed");

			return;
		}

		

		if (SDL_Init(SDL_INIT_AUDIO) != 0) {
			//end the game and log failure
			bIsGameOver = true;

			SDL_Log("Audio subsystem - failed");

			return;
		}
		else {
			//activate the audio if successful

			//@param 1 - The audio device frequency, specified in Heartz (Hz); In modern time 48000 is reasonable as default
			//@param 2 - The SDL audio format; SDL uses this to know what format to read the audio as
			//@param 3 - Audio channels, 1 - Mono and 2 - Stereo
			//@param 4 - BitChunks; The latency the audio device will send to the audio listener; Lower = Faster; Ideal values are betweem 1024 & 4096;
		
			Mix_OpenAudio(48000, MIX_DEFAULT_CHANNELS, 2, 4096);
			
		}

		//enable game loop
		bIsGameOver = false;
		//if the subsystem succesfully initialises
		cout << "initialise SDL - success" << endl;
	}

}

//deconstructor
Game::~Game()
{
	vector<GameObject*>().swap(subGameObjects);
}

void Game::addRandomRectangle(bool bFilled)
{
	//randomise all the variables of the rectangle
	//randomising the width and height but with a MIN value of 10 and a MAX of 150
	float w = rand() % 150 + 10;
	float h = rand() % 150 + 10;
	//randomise the position but make sure the center doesn't go outside of the window
	float posX = rand() % 980;
	float posY = rand() % 540;

	//randomise the colour
	//we're using 256 because rand will ignore the last value and MAX at 255
	SDL_Colour newColour = { rand() % 256, rand() % 256, rand() % 256, rand() % 256 };

	//create the rectangle using the above parameters
	RectangleObject* newRectangle = new RectangleObject(w, h, Vector2(posX, posY), newColour, bFilled);
	subGameObjects.push_back(newRectangle);
}

bool Game::Start()
{
	// create the SDL renderer and define it
	//assigning the correct renderer to the correct window
	sdlRenderer[0] = SDL_CreateRenderer(sdlWindow[0], 0, -1);
	sdlRenderer[1] = SDL_CreateRenderer(sdlWindow[1], 0, -1); /*creating the second parameter*/

	lastUpdatedTime = SDL_GetTicks();
	
	//make both the renderer worked
	if (sdlRenderer[0] != nullptr && sdlRenderer[1] != nullptr) {
		cout << "Create Renderer - success" << endl;

		//Start detecting input
		userInput = new Input(this);		

		//create a starter game state
		MenuState* starterGameState = new MenuState();
		starterGameState->stateID = 0;
		//make sure the game state starts
		starterGameState->onEnter(sdlRenderer[0], sdlWindow[0]);
		gameStates.push_back(starterGameState);

		return true;
	}
	
	cout << "Create Renderer - failed" << endl;

	return false;
}

void Game::ProcessInput()
{
	userInput->updateInput(bIsGameOver, sdlWindow);

	//run the game state process input
	gameStates.back()->processInput(userInput);
}

void Game::Update()
{

	//how long has it been since the last frame updated in milliseconds
	unsigned int tick = SDL_GetTicks() - lastUpdatedTime;

	//change the tick to seconds
	float deltaTime = tick / 1000.0f;

	//Refresh the last update time
	lastUpdatedTime = SDL_GetTicks();

	//1000ms per second
	if (SDL_GetTicks() > 5000) {
		//if the game state is running the 0 ID
		if (gameStates.back()->stateID == 0) {
			//telling the state it's exited
			gameStates.back()->onExit();
			//deallocate the state from memory
			delete gameStates.back();
			//reduce the size of the vector
			gameStates.pop_back();

			//create a new play state
			PlayState* newPlayState = new PlayState();
			//change the ID so this if condition doesn't run again
			newPlayState->stateID = 1;
			//Tell the game state it's started
			newPlayState->onEnter(sdlRenderer[0], sdlWindow[0]);
			//add it to the gameStates stack
			gameStates.push_back(newPlayState);
		}
	}

	//run the game state update
	gameStates.back()->update(deltaTime);
}

void Game::Draw()
{
	//set the draw color
	SDL_SetRenderDrawColor(sdlRenderer[0], 15, 15, 15, 255);
	
	/*
	//set background colour of second window
	SDL_GetRenderDrawColor(sdlRenderer[1], 15, 15, 15, 225);
	*/

	//clear the renderer
	for (vector<SDL_Renderer*>::iterator it = sdlRenderer.begin(); it < sdlRenderer.end(); ++it) {
		SDL_RenderClear(*it);
	}
	
	//draw secondary objects to the secondary renderer
	for (vector<GameObject*>::iterator it = subGameObjects.begin(); it < subGameObjects.end(); ++it) {
		(*it)->draw(sdlRenderer[1]);
	}

	//run and draw in our game state
	gameStates.back()->draw(sdlRenderer[0]);
	
	//getting all the newly renderer stuff and showing it onto the window
	for (vector<SDL_Renderer*>::iterator it = sdlRenderer.begin(); it < sdlRenderer.end(); ++it) {
		SDL_RenderPresent(*it);
	}

	
}

void Game::HandleGarbage()
{
	//run the game state Handle Garbage
	gameStates.back()->handleGarbage();
}

void Game::Run(const char* title, int width, int height, bool fullscreen)
{
	//define the creation flag
	int creationFlag = 0;

	//if fullscreen is set to false then set to window mode
	if (!fullscreen) {
		creationFlag = SDL_WINDOW_SHOWN;

	}

	else {
		creationFlag = SDL_WINDOW_FULLSCREEN;
	}

	sdlWindow[0] = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, creationFlag);

	sdlWindow[1] = SDL_CreateWindow("BGEngine Secondary Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_HIDDEN); /*Create second SDL window*/

	//check if the SDL window work
	////create the renderer and start game loop
	if (sdlWindow[0] != nullptr && sdlWindow[1] != nullptr && Start()) {
		cout << "Create window - success" << endl;

		//get window information for the system that we can use to add the menu to
		SDL_SysWMinfo windowInfo;
		//get the version of SDL we are using and add it into the windowInfo
		SDL_VERSION(&windowInfo.version);
		//we then assign the rest of the information about the sdlwindow into the variable
		SDL_GetWindowWMInfo(sdlWindow[0], &windowInfo);
		
		//we're gonna convert our SDL window into a windows window and store it
		HWND hWindow = windowInfo.info.win.window;
		//we need to get the menu from our resources header
		//GetModuleHandle() return the name of the program that we are currently running
		//MAKEINTRESOURCE() convert the ID of the menu into the required format LPCWSTR
		HMENU hMenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));

		SetMenu(hWindow, hMenu);

		//run the loop
		while (!bIsGameOver) {
			//delete gameobjects that are marked for delete
			HandleGarbage();

			//check for the player input
			ProcessInput();

			//process any changes that were made either by input or game code
			Update();

			//draw everything to screen
			Draw();

		}
	}

	//debug or was exited
	cout << "Create Window - failed or was exited" << endl;

	Shutdown();
	Destroy();


}

void Game::Shutdown()
{
}

void Game::Destroy()
{
	//dealocate the window
	SDL_DestroyWindow(sdlWindow[0]);
	SDL_DestroyWindow(sdlWindow[1]);

	//dealocate the renderer
	SDL_DestroyRenderer(sdlRenderer[0]);
	SDL_DestroyRenderer(sdlRenderer[1]);

	//shutdown the SDL framework
	SDL_Quit();

}

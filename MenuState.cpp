#include "MenuState.h"

MenuState::MenuState()
{
	defaultBackgroundColour = { 0, 0, 0, 0 };
	menuTitle = nullptr;
	sfx_enter = nullptr;
}

void MenuState::draw(SDL_Renderer* renderer)
{
	GameState::draw(renderer);

	if (menuTitle != nullptr) {
		//draw menu title if exists
		menuTitle->draw(renderer);
	}
}

bool MenuState::onEnter(SDL_Renderer* renderer, SDL_Window* window)
{
	SDL_Log("Entered Menu State...");

	//define a window width and height
	int wWidth, wHeight = 0;
	SDL_GetWindowSize(window, &wWidth, &wHeight);

	//define the half width and height to get the center of the screen
	int halfWindowWidth = SDL_max(wWidth, 1) / 2;
	int halfWindowHeight = SDL_max(wHeight, 1) / 2;


	//create the text as an object 
	menuTitle = new Text();

	//define a colour for the title
	SDL_Colour titleColour = { 255, 255, 255, 255 };

	//initialise the font
	if (!menuTitle->initialiseFont(renderer, "Assets/VT323-Regular.ttf", 42, "Welcome SimpleGameEG", titleColour, Vector2(halfWindowWidth, halfWindowHeight))) {
		delete menuTitle;
		menuTitle = nullptr;
	}
	else {
		//menuTitle->changeText("This is the new text...");
		menuTitle->centerText(true);
	}

	//define the sound effect
	sfx_enter = Mix_LoadWAV("Assets/EntryAudio.wav");

	//play the sound effect
	//@param 3 - loop amounts: -1 = indefinetely, 0 = no loops, 1 or higher = amount specified
	if (sfx_enter != nullptr) {
		Mix_PlayChannel(-1, sfx_enter, 0);
	}

	return true;
}

bool MenuState::onExit()
{
	SDL_Log("Exited Menu State...");

	//deallocate menu title from memory;
	if (menuTitle != nullptr) {
		delete menuTitle;
		menuTitle = nullptr;
	}

	if (sfx_enter != nullptr) {
		Mix_FreeChunk(sfx_enter);
		sfx_enter = nullptr;
	}

	return true;
}

#include "Input.h"
#include "SDL_syswm.h"
#include "resource.h"
#include "Game.h"

Input::Input(Game* myGame)
{
	keyboardState = nullptr;
	this->myGame = myGame;
	//allow SDL to detect menu input events
	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
}

Input::~Input()
{
}

void Input::updateInput(bool& bIsGameOver, vector<SDL_Window*> sdlWindows)
{
	SDL_Event aEvent;
	while (SDL_PollEvent(&aEvent)) {

		//detect the type of input used
		switch (aEvent.type) {
		
		case SDL_KEYDOWN:
			keyboardState = SDL_GetKeyboardState(NULL);
			break;

		case SDL_KEYUP:
			keyboardState = SDL_GetKeyboardState(NULL);
			break;

		case SDL_SYSWMEVENT:
			handleMenuEvents(&aEvent, sdlWindows, bIsGameOver);
			break;

		default:
			break;

			

		}

		//when you hit the cross button on the app, close the game
		if (aEvent.window.event == SDL_WINDOWEVENT_CLOSE) {
			//if the main window close was pressed - end event
			if (aEvent.window.windowID == SDL_GetWindowID(sdlWindows[0])) {
				bIsGameOver = true;
			}
			else {
				//if the secondary window close was pressed then hide the secondary window
				SDL_HideWindow(sdlWindows[1]);
			}
		}
	}
}

bool Input::isKeyDown(SDL_Scancode key)
{
	if (keyboardState != nullptr && keyboardState[key] == true) {
		return true;
	}

	return false;
}

bool Input::isKeyUp(SDL_Scancode key)
{
	if (keyboardState != nullptr && keyboardState[key] == true) {
		return false;
	}

	return true;
}

void Input::handleMenuEvents(SDL_Event* aEvent, vector<SDL_Window*> sdlWindows, bool &bIsGameOver)
{
	switch (aEvent->syswm.msg->msg.win.wParam) {
	case ID_FILE_NEWWINDOW: //if we push a new window button
		SDL_ShowWindow(sdlWindows[1]); //show a secondary window
		break;

	case ID_FILE_EXITGAME: //if we push the exit game button
		bIsGameOver = true; //exit game
		break;

	case ID_HELP_ABOUTBGENGINE: //if we push about the bgengine menu buttom
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "About the BGEngine", "BGEngine v8 is an SDL2 based game engine.", sdlWindows[0]); // create a message box that can be closed when pressing the ok button
		break;

	case ID_SHAPES_RECTANGLE: //if shapes > rectangle menu is pressed
		myGame->addRandomRectangle(false); //spawn an empty rectangle
		break;
		
	case ID_SHAPES_RECTANGLEFUFILLED: //if shapes > rectangle(filled) menu is pressed
		myGame->addRandomRectangle(true); //spawn a filled rectangle
		break;

	default:
		break;
	}
}

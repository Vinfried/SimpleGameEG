#pragma once
#include "SDL.h"
#include <iostream>
#include <string>
#include "Vector2.h"
//using the SDL font library
#include "SDL_ttf.h"

using namespace std;

class Text
{
public:
	Text();
	~Text();

	//Initialise the fonts and return a boolean
	//@param fontPath - The path to the font in your project
	//@param textToRender - The text that will be rendered to the screen - global
	bool initialiseFont(SDL_Renderer* renderer, string fontPath, int fontSize, string textToRender, const SDL_Colour colour, Vector2 position = Vector2(0.0f, 0.0f));

	//Draw to the renderer
	void draw(SDL_Renderer* renderer);

	//update text with new text
	void changeText(string newText);

	//get the width and height of the textbox
	Vector2 getTextDimentions();


	//center the text using it's dimentions
	void centerText(bool bCenterText);

protected:
	//this will actually define and render the text
	bool setText(SDL_Renderer* renderer);

	//this will store a font - this is not the text just the font file
	TTF_Font* font;

	//to render to the screen we need a surface and a texture
	//surface converts to texture
	SDL_Surface* textSurface;

	//texture renders to the screen
	SDL_Texture* textTexture;

	//rectangle to render from the texture
	SDL_Rect textBox;

	//bool to decide if we need to update the text
	bool bShouldUpdateText;
	//center text bool
	bool bCenterText;

	//text rendering variables
	//colour
	SDL_Colour colour;
	//text to render
	string textToRender;
	
	//position of the text to screen
	Vector2 position;

};


#include "Text.h"

Text::Text()
{
	colour = { 255, 255, 255, 255 };
	font = nullptr;
	textBox = {};
	textSurface = nullptr;
	textTexture = nullptr;
	bShouldUpdateText = false;
	bCenterText = false;
}

Text::~Text()
{
	if (textTexture != nullptr) {
		SDL_DestroyTexture(textTexture);
		textTexture = nullptr;
	}

	//deallocate the font
	if (font != nullptr) {
		TTF_CloseFont(font);
		font = nullptr;
	}
}

bool Text::initialiseFont(SDL_Renderer* renderer, string fontPath, int fontSize, string textToRender, const SDL_Colour colour, Vector2 position)
{
	//initialise our global variables
	this->textToRender = textToRender;
	this->colour = colour;
	this->position = position;

	//load the font
	font = TTF_OpenFont(fontPath.c_str(), fontSize);

	//return true if able to create the text
	return setText(renderer);

	return true;
}

void Text::draw(SDL_Renderer* renderer)
{
	//change the text if we need to
	if (bShouldUpdateText) {
		setText(renderer);

		//make sure his only runs when it needs to
		bShouldUpdateText = false;
	}

	if (bCenterText) {
		//center the text by subtracting it's position by it's dimentions (x - width)(y - height)
		int halfWidth = SDL_max(textBox.w, 1) / 2;
		int halfHeight = SDL_max(textBox.h, 1) / 2;

		textBox.x -= halfWidth;
		textBox.y -= halfHeight;

		bCenterText = false;
	}

	//render the text to the screen/renderer
	SDL_RenderCopy(renderer, textTexture, nullptr, &textBox);

}

void Text::changeText(string newText)
{
	//change the text to the screen/renderer
	textToRender = newText;
	//tell the draw it can update the text
	bShouldUpdateText = true;	
}

Vector2 Text::getTextDimentions()
{
	return Vector2(textBox.w, textBox.h);
}

void Text::centerText(bool bCenterText)
{
	this->bCenterText = bCenterText;
}

bool Text::setText(SDL_Renderer* renderer)
{
	//make sure the font loaded correctly
	if (font == nullptr) {

		//if the font is nullptr the it couldn't find the path
		SDL_Log("Font not found... %s", SDL_GetError());

		return false;
	}

	//create a surface of the font and message
	textSurface = TTF_RenderText_Solid(font, textToRender.c_str(), colour);

	//make sure the surface loaded correctly
	if (textSurface == nullptr) {

		//if surface failed to create
		SDL_Log("Text Surface - Failed");

		return false;
	}

	//if there is already a texture assigned 
	if (textSurface != nullptr) {
		
		//destroy it and make room for new text
		SDL_DestroyTexture(textTexture);
		textTexture = nullptr;

	}

	//create texture from the surface
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	//make sure the texture loaded correctly
	if (textTexture == nullptr) {
		//if the texture failed to create
		SDL_Log("Text Texture - Failed");

		SDL_FreeSurface(textSurface);

		return false;
	}

	//create render space
	//converting the floating points from the position vector into integers
	textBox = { static_cast<int>(position.x), static_cast<int>(position.y), textSurface->w, textSurface->h };
	
	//deallocate the surface
	SDL_FreeSurface(textSurface);

	return true;
}

#include "RectangleObject.h"

RectangleObject::RectangleObject(float width, float height, Vector2 position, SDL_Colour colour, bool bFilled)
{
	this->width = width;
	this->height = height;
	this->position = position;
	this->colour = colour;
	this->bFilled = bFilled;

}

void RectangleObject::draw(SDL_Renderer* renderer)
{
	SDL_FRect rectangle = {width, height, position.x, position.y};

	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);

	//if bFilled == false
	if (!bFilled) {
		//draw outlined rectangle
		SDL_RenderDrawRectF(renderer, &rectangle);
	}
	else {
		//draw rectangle with filled colour
		SDL_RenderFillRectF(renderer, &rectangle);
	}
}

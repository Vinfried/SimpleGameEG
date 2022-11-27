#pragma once
#include "GameObject.h"
class RectangleObject :
    public GameObject
{
public:
    RectangleObject(float width, float height, Vector2 position, SDL_Colour colour, bool bFilled);

    void draw(SDL_Renderer* renderer) override;

protected:
    float width;
    float height;
    //screen position
    Vector2 position;
    //this will decide if the rectangle is filled with colour
    bool bFilled;
    SDL_Colour colour;
};


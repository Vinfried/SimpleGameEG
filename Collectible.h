#pragma once
#include "GameObject.h"
#include "SDL.h"
#include "Vector2.h"

class Collectible :
    public GameObject
{
public:
    Collectible(Texture* collectibleTexture, Vector2 pos, int numberOfFrames = 1);
    ~Collectible();

    void draw(SDL_Renderer* renderer) override;
    virtual void update(float deltaTime) override;

private:
    //velocity is the true representation of speed, this will gave a x and y value
    Vector2 velocity;
    //this is going to detect input and move our character based on it's direction
    //make sure the number is normally between 0 and 1
    Vector2 movementAxis;
};


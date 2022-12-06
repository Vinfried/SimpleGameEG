#pragma once
#include "GameObject.h"
#include "SDL.h"
#include "Vector2.h"
#include "Animation.h"

struct CharacterAnimations {
    Animation* attack;
    Animation* idle;
    Animation* run;
    Animation* die;
    Animation* jump;
};

class Character :
    public GameObject
{
public:
    Character(Texture* characterTexture, Vector2 pos, int numberOfFrames = 1);
    ~Character() {}

    void draw(SDL_Renderer* renderer) override;
    virtual void update(float deltaTime) override;
    virtual void processInput(Input *userInput) override {}

protected:
    float maxSpeed;

    void setMovementAxis(Vector2 axis);
    Vector2 getMovementAxis();
    //velocity is the true representation of speed, this will gave a x and y value
    Vector2 velocity;

private:

    
    //this is going to detect input and move our character based on it's direction
    //make sure the number is normally between 0 and 1
    Vector2 movementAxis;
};


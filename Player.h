#pragma once
#include "Character.h"
#include "Animation.h"
enum class playerStates
{
    idle,
    run,
    attack,
    die,
    jump
};

class Player :
    public Character
{
public:
    Player(Texture* characterTexture, Vector2 pos, int numberOfFrames = 1);
    ~Player();
    void draw(SDL_Renderer* renderer) override;
    void update(float deltaTime) override;
    virtual void processInput(Input *userInput) override;
    bool flip = false;
    bool attack = false;
    CharacterAnimations playerAnims;
    playerStates animationStates;
    

};


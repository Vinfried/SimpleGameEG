#pragma once
#include "Character.h"
#include "Animation.h"
class Player :
    public Character
{
public:
    Player(Texture* characterTexture, Vector2 pos, int numberOfFrames = 1);
    ~Player();
    void update(float deltaTime) override;
    virtual void processInput(Input *userInput) override;
    CharacterAnimations playerAnims;

};


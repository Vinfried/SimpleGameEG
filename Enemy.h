#pragma once
#include "Character.h"
#include "Vector2.h"

class Enemy :
    public Character
{
public:
    Enemy(Texture* characterTexture, Vector2 pos, int numberOfFrames = 1);
    ~Enemy();

    void update(float deltaTime) override;
    virtual void processInput(Input *userInput) override;
};


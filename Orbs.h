#pragma once
#include "Collectible.h"
class Orbs :
    public Collectible
{
public:
    Orbs(Texture* collectibleTexture, Vector2 pos, int numberOfFrames = 1);
    ~Orbs();

    void update(float deltaTime) override;
};


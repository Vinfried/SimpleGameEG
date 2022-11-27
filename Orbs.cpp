#include "Orbs.h"

Orbs::Orbs(Texture* collectibleTexture, Vector2 pos, int numberOfFrames)
:Collectible::Collectible(collectibleTexture, pos, numberOfFrames)
{
	tag = "Orb";
}

Orbs::~Orbs()
{
}

void Orbs::update(float deltaTime)
{
	Collectible::update(deltaTime);
}

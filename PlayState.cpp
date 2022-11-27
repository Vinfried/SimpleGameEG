#include "PlayState.h"
#include "Player.h"
#include "Enemy.h"
#include "Orbs.h"
#include <string>


PlayState::PlayState()
{
	defaultBackgroundColour = { 255, 0, 255, 255 };
	txt_pPosition = nullptr;
	pChar = nullptr;
	music_bg = nullptr;
}

void PlayState::update(float deltaTime)
{
	GameState::update(deltaTime);

	//make sure the text and the player character exists
	if (pChar != nullptr && txt_pPosition != nullptr) {
		//initialise some integers to use for concatenation
		//use integers so that we don't display decimals
		int x, y = 0;

		//set the x and y to the players position
		//convert the floats into integers
		x = static_cast<int>(pChar->getPosition().x);
		y = static_cast<int>(pChar->getPosition().y);

		//form and concatenate the string
		string newText = "X: " + to_string(x) + ", Y: " + to_string(y);
	
		//run the new text
		txt_pPosition->changeText(newText);

		pChar->playerAnims.run->update(deltaTime);
	}
}

void PlayState::draw(SDL_Renderer* renderer)
{
	GameState::draw(renderer);
	float x, y = 0;
	x = pChar->getPosition().x;
	y = pChar->getPosition().y;

	if (txt_pPosition != nullptr) {
		txt_pPosition->draw(renderer);
	}
	pChar->playerAnims.run->draw(renderer, Vector2(x, y));
}

bool PlayState::onEnter(SDL_Renderer* renderer, SDL_Window* window)
{
	//initialise the player texture
	Texture* playerTexture = new Texture();
	//load the texture
	playerTexture->loadImageFromFile("Assets/hero_spritesheet_50x37_109.png", renderer);
	//construct the player as a character
	pChar = new Player(playerTexture, Vector2(0, 0), 109);
	pChar->tag = "Player";
	//load animations
	pChar->playerAnims.attack = new Animation(playerTexture, 109, 0.1f, 0, 12);
	pChar->playerAnims.idle = new Animation(playerTexture, 109, 0.1f, 65, 68);
	pChar->playerAnims.run = new Animation(playerTexture, 109, 0.1f, 84, 89);
	
	gameObjectStack.push_back(pChar);
	
	//intialised the enemy texture
	Texture* enemyTexture = new Texture();
	//load the enemy texture
	enemyTexture->loadImageFromFile("Assets/goblin-spritesheet-65x35-28.png", renderer);

	//construct the enemy as a Enemy using the enemy texture
	Enemy* enemyCharacter = new Enemy(enemyTexture, Vector2(0, 0), 28);
	gameObjectStack.push_back(enemyCharacter);
	//boxColliders.push_back(enemyCharacter->getCollision());

	//intialised the enemy texture
	enemyTexture = new Texture();
	//load the enemy texture
	enemyTexture->loadImageFromFile("Assets/goblin-spritesheet-65x35-28.png", renderer);

	//construct the second enemy using the same texture
	Enemy* enemyCharacter2 = new Enemy(enemyTexture, Vector2(0, 50), 28);
	gameObjectStack.push_back(enemyCharacter2);
	//boxColliders.push_back(enemyCharacter2->getCollision());

	//initialise collectible(orb) texture
	Texture* orbsTexture = new Texture();
	//load the orb texture
	orbsTexture->loadImageFromFile("Assets/rotating_orbs_128x32-4.png",renderer);
	//construct the orb as a collectible
	Orbs* orb = new Orbs(orbsTexture, Vector2(80, 150), 4);
	gameObjectStack.push_back(orb);
	//boxColliders.push_back(orb->getCollision());

	txt_pPosition = new Text();

	SDL_Colour textColour = { 255, 255, 255, 255 };

	if (!txt_pPosition->initialiseFont(renderer, "Assets/VT323-Regular.ttf", 24,
		"X: 0, Y: 0", textColour, Vector2(15.0f, 15.0f))) {
		
		delete txt_pPosition;
		txt_pPosition = nullptr;
	}

	//play and music and load it
	music_bg = Mix_LoadMUS("Assets/BackgoundMusic.wav");

	if (music_bg != nullptr) {
		Mix_PlayMusic(music_bg, -1);
	}

    return true;
}

bool PlayState::onExit()
{
    SDL_Log("Exited Playstate");

	if (pChar != nullptr) {
		pChar = nullptr;
	}

	if (txt_pPosition != nullptr) {
		txt_pPosition = nullptr;
	}

	if (music_bg != nullptr) {
		Mix_FreeMusic(music_bg);
		music_bg = nullptr;
	}

    return true;
}

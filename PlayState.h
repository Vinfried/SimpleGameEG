#pragma once
#include "GameState.h"
#include "Player.h"
#include "Text.h"
#include "SDL_mixer.h"

class PlayState :
    public GameState
{
public:
    PlayState();
    virtual void update(float deltaTime) override;
    virtual void draw(SDL_Renderer* renderer) override;
    virtual void processInput(Input* userInput) override { GameState::processInput(userInput); }

    virtual bool onEnter(SDL_Renderer* renderer, SDL_Window* window) override;
    virtual bool onExit() override;

protected:
    //store a pointer to the player game object
    Player* pChar;

    //store the text for the positon
    Text* txt_pPosition;

    //background music
    Mix_Music* music_bg;
};


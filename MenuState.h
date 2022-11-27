#pragma once
#include "GameState.h"
#include "Text.h"
#include "SDL_mixer.h"

class MenuState :
    public GameState
{
public:
    MenuState();
    virtual void update(float deltaTime) override { GameState::update(deltaTime); }
    virtual void draw(SDL_Renderer* renderer) override;
    virtual void processInput(Input* userInput) override { GameState::processInput(userInput); }

    virtual bool onEnter(SDL_Renderer* renderer, SDL_Window* window) override;
    virtual bool onExit() override;

protected:
    Text* menuTitle;
    Mix_Chunk* sfx_enter;

};


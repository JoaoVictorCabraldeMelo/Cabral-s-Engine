#include "../lib/State.hpp"
#include <iostream>
#include <fstream>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "../lib/SDL_include.h"

State::State()
{
  this->quitRequested = false;
  this->bg = *new Sprite("./src/assets/sprites/monk.png");
  this->music = *new Music("./src/assets/music/hells.ogg");
}

void State::LoadAssets()
{
  this->bg.Open("./src/assets/sprites/monk.png");
  this->music.Open("./src/assets/music/hells.ogg");
}

void State::Update(float dt)
{
  if (SDL_QuitRequested())
  {
    this->quitRequested = true;
  }
}

void State::Render()
{
  this->bg.Render(100, 100);
}

bool State::QuitRequested()
{
  return this->quitRequested;
}


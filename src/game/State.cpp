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
  this->bg = new Sprite();
  this->music = new Music();
}

void State::LoadAssets(std::string fileMusic, std::string fileImage)
{
  this->bg.Open(fileImage);
  this->music.Open(fileMusic);
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


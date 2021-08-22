#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include "./State.hpp"

class Game
{

private:
  std::string title;
  int width;
  int height;

  static Game *instance;
  SDL_Window *window;
  SDL_Renderer *renderer;
  State *state;

  Game(std::string title, int width, int height);

public:
  ~Game();

  void Run();

  SDL_Renderer *GetRenderer();

  static Game &GetInstance();

  State &GetState();
};


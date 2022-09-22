#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <SDL2/SDL.h>
#include "State.hpp"

class Game
{

private:
  std::string title;

  int width;
  int height;

  /*Temporização */
  int frameStart = (int) SDL_GetTicks();
  float dt{0.0};

  static Game *instance;
  SDL_Window *window;
  SDL_Renderer *renderer;
  State *state;

  Game(std::string title, int width, int height);

  void CalculateDeltaTime();

public:
  ~Game();

  void Run();

  SDL_Renderer *GetRenderer();

  static Game &GetInstance();

  State &GetState();

  float GetDeltaTime();

  int GetHeight();

  int GetWidth();
};

#endif
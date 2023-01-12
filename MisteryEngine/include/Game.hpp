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

  std::vector<SDL_Rect> displaysSize;
  Vec2 screenScale{1.0F, 1.0F};

  Game(std::string title, int width, int height);

  void CalculateDeltaTime();

  void GetDisplaysSizes();

  void SetScreenScale();

public:
  ~Game();

  void Run();

  SDL_Renderer *GetRenderer();

  static Game &GetInstance();

  State &GetState();

  float GetDeltaTime();

  int GetHeight();

  int GetWidth();

  Vec2 GetScreenScale();

  SDL_Rect GetScreen();
};

#endif
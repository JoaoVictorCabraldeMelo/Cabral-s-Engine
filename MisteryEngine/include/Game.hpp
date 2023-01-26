#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <SDL2/SDL.h>
#include "State.hpp"
#include <stack>

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

  State *storedState;

  std::stack<std::unique_ptr<State>> stateStack;

  void CalculateDeltaTime();

  void GetDisplaysSizes();

  void SetScreenScale();

public:
  Game(std::string title, int width, int height);

  ~Game();

  void Run();

  static Game &GetInstance();

  SDL_Renderer *GetRenderer();

  State &GetCurrentState();

  void Push(State *state);

  float GetDeltaTime();

  int GetHeight();

  int GetWidth();

  Vec2 GetScreenScale();

  SDL_Rect GetScreen();
};

#endif
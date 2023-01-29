#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <SDL2/SDL.h>
#include "State.hpp"
#include "Vec2.hpp"
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

  std::vector<SDL_Rect> displaysSize;

  Vec2 screenScale = {1, 1};

  void CalculateDeltaTime();

  void GetDisplaysSizes();

  void SetScreenScale();

public:
  Game(const std::string& title, const int width, const int height);

  ~Game();

  void Run();

  static Game &GetInstance();

  SDL_Renderer *GetRenderer();

  State &GetCurrentState();

  void Push(State *state);

  float GetDeltaTime() const;

  int GetHeight() const;

  int GetWidth() const;

  Vec2 GetScreenScale() const;

  SDL_Rect GetScreen() const;
};

#endif
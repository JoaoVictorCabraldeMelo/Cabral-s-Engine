
#include <iostream>
#include <SDL2/SDL.h>

class Game
{

private:
  std::string title;
  int width;
  int height;

  static constexpr Game *instance = nullptr;
  SDL_Window *window;
  SDL_Renderer *renderer;
  
  Game(std::string title, int width, int height);

public:

  ~Game();

  void Run();

  SDL_Renderer *GetRenderer();

  static Game &GetInstance();
};


#include "../include/Game.hpp"
#include "../include/TitleState.hpp"
#include <ctime>
#include <cstdlib>

int main() {

  srand (static_cast <unsigned> (time(0)));

  Game &game = Game::GetInstance();
  
  State *initial_state = new TitleState();

  game.Push(initial_state);

  game.Run();

  return 0;
}
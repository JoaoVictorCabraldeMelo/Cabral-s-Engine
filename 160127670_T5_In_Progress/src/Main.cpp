#include "../include/Game.hpp"
#include <ctime>
#include <cstdlib>

int main() {

  srand (static_cast <unsigned> (time(0)));

  Game &game = Game::GetInstance();

  game.Run();

  return 0;
}
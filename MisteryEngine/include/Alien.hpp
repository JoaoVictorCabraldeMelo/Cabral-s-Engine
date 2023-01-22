#ifndef _ALIEN_H_
#define _ALIEN_H_

#include "Component.hpp"
#include "Vec2.hpp"
#include "Minion.hpp"
#include "Timer.hpp"


class Alien : public Component
{
public:
  Alien(GameObject &associated, int nMinions);

  ~Alien();

  void Start();

  void Update(float dt);

  void Render();

  bool Is(std::string type);

  void NotifyCollision(GameObject &other);

  int hp;

  static size_t alienCount;

private:

  enum AlienState
  {
    MOVING,
    RESTING
  };

  AlienState state;

  Timer restTimer;

  Vec2 destination;

  int nMinions;

  Vec2 speed;

  std::vector<std::weak_ptr<GameObject>> minionArray;

};


#endif
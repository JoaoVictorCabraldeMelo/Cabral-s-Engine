#ifndef _ALIEN_H_
#define _ALIEN_H_

#include "Component.hpp"
#include "Vec2.hpp"
#include "Minion.hpp"

#include <queue>


#define SPEEDX 200
#define SPEEDY 200

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

private:
  class Action
  {
  public:
    enum ActionType
    {
      MOVE,
      SHOOT
    };

    Action(ActionType Action, float x, float y);

    ActionType type;

    Vec2 pos;
  };

  int nMinions;

  Vec2 speed;

  std::queue<Action> taskQueue;

  std::vector<std::weak_ptr<GameObject>> minionArray;

};


#endif
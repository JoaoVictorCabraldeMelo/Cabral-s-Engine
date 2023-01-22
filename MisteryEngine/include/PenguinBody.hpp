#ifndef _PENGUIN_BODY_H_
#define _PENGUIN_BODY_H_

#include "Component.hpp"
#include "Vec2.hpp"

class PenguinBody : public Component
{
public:
  PenguinBody(GameObject &associated);

  ~PenguinBody();

  void Update(float dt);

  void Start();

  void Render();

  bool Is(std::string type);

  void NotifyCollision(GameObject &other);

  static PenguinBody *player;

  int hp;

private:
  std::weak_ptr<GameObject> pcannon;

  Vec2 speed;

  float linearSpeed;

  float angle;
};

#endif
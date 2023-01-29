#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <iostream>
#include <memory>

#include "Rect.hpp"
#include <vector>
#include "Component.hpp"

class Component;

class GameObject
{
public:
  bool started;

  GameObject();

  ~GameObject();

  void Update(float dt);

  void Render();

  bool IsDead() const;

  void Start();

  void RequestDelete();

  void AddComponent(Component *cpt);

  void RemoveComponent(Component *cpt);

  Component *GetComponent(const std::string& type) const;

  void NotifyCollision(GameObject &other);

  Rect box;

  double angleDeg;

private:

  std::vector <std::unique_ptr<Component>> components;

  bool isDead;
};

#endif

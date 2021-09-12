#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_


class GameObject;

#include <iostream>
#include <memory>

#include "Rect.hpp"
#include <vector>
#include "Component.hpp"

class GameObject
{
private:

  std::vector <std::unique_ptr<Component>> components;

  bool isDead;

public:

  GameObject();

  ~GameObject();

  void Update(float dt);

  void Render();

  bool IsDead();

  void RequestDelete();

  void AddComponent(std::unique_ptr<Component> &cpt);

  void RemoveComponent(std::unique_ptr<Component> &cpt);

  Component* GetComponent(std::string type);
  
  Rect box;
};

#endif

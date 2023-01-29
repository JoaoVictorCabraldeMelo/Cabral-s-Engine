#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject.hpp"
#include <iostream>

class GameObject;

class Component
{
public:
  GameObject &associated;

  Component(GameObject &associated);

  virtual ~Component();

  virtual void Update(float dt) = 0;

  virtual void Render() = 0;

  virtual bool Is(const std::string& type) = 0;

  virtual void Start();

  virtual void NotifyCollision(GameObject &other);
};

#endif
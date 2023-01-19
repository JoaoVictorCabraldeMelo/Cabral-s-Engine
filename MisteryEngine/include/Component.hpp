#ifndef COMPONENT_H
#define COMPONENT_H

class Component;

#include "GameObject.hpp"
#include <iostream>

class Component
{
protected:
  GameObject &associated;

public:

  explicit Component(GameObject &associated);

  virtual ~Component();

  virtual void Update(float dt) = 0;

  virtual void Render() = 0;

  virtual bool Is(std::string type) = 0;

  virtual void Start();

  virtual void NotifyCollision(GameObject &other);
};

#endif
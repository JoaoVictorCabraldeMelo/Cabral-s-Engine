
#include "../include/Component.hpp"
#include "../include/GameObject.hpp"

#include <algorithm>

using namespace std;

GameObject::GameObject()
{
  this->isDead = false;
}

GameObject::~GameObject()
{
  for (auto component : this->components)
    delete component;
  this->components.clear();
}

void GameObject::Update(float dt)
{
  for (auto &component : this->components)
    component->Update(dt);
}

void GameObject::Render()
{
  for (auto &component : this->components)
    component->Render();
}

bool GameObject::IsDead()
{
  return this->isDead;
}

void GameObject::RequestDelete()
{
  this->isDead = true;
}

void GameObject::AddComponent(Component *cpt)
{
  this->components.push_back(cpt);
}

void GameObject::RemoveComponent(Component *cpt)
{
  vector<Component *>::iterator position = find(this->components.begin(), this->components.end(), cpt);

  if (position != this->components.end())
    this->components.erase(position);
}

Component *GameObject::GetComponent(string type)
{
  vector<Component *>::iterator it;

  for (it = this->components.begin(); it != this->components.end() && !(*it)->Is(type); ++it)
  {
  }

  if (it == this->components.end())
    return nullptr;
  else
    return *it;
}

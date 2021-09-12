
#include "../include/Component.hpp"
#include "../include/GameObject.hpp"

#include <algorithm>
#include <memory>

using namespace std;

GameObject::GameObject()
{
  this->isDead = false;
}

GameObject::~GameObject()
{
  vector<unique_ptr<Component>>::iterator it;

  auto begin = this->components.begin();

  auto end = this->components.end();

  for (it = end; it != begin; --it)
    it->reset();

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

void GameObject::AddComponent(std::unique_ptr<Component> &cpt)
{
  this->components.emplace_back(cpt.get());
}

void GameObject::RemoveComponent(std::unique_ptr<Component> &cpt)
{
  vector<unique_ptr<Component>>::iterator position = find(this->components.begin(), this->components.end(), cpt);

  if (position != this->components.end())
    this->components.erase(position);
}

Component* GameObject::GetComponent(string type)
{
  vector<unique_ptr<Component>>::iterator it;

  for (it = this->components.begin(); it != this->components.end() && !(*it)->Is(type); ++it)
  {
  }

  if (it == this->components.end())
    return nullptr;
  else
    return it->get();
}

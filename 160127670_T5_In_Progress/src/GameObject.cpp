
#include "../include/Component.hpp"
#include "../include/GameObject.hpp"

#include <algorithm>
#include <memory>

using namespace std;

GameObject::GameObject()
{
  this->isDead = false;
  this->started = false;
}

GameObject::~GameObject()
{
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
  this->components.emplace_back(cpt);
  if (this->started)
    cpt->Start();
}

void GameObject::RemoveComponent(Component *cpt_recebido)
{
  remove_if(this->components.begin(), this->components.end(), [=](unique_ptr<Component> &cpt_alocado) { return cpt_recebido == cpt_alocado.get(); });
}

void GameObject::Start()
{
  for (auto &component : this->components)
  {
    component->Start();
  }
  this->started = true;
}

Component *GameObject::GetComponent(string type)
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

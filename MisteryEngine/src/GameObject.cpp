
#include "../include/Component.hpp"
#include "../include/GameObject.hpp"

#include <algorithm>
#include <memory>

using namespace std;

GameObject::GameObject()
{
  this->isDead = false;
  this->started = false;
  this->angleDeg = 0;
}

GameObject::~GameObject()
{
  this->components.clear();
}

void GameObject::Update(float dt)
{
  for (int i = 0; i < (int)this->components.size(); i++)
    this->components[i]->Update(dt);
}

void GameObject::Render()
{
  for (int i = 0; i < (int)this->components.size(); i++)
    this->components[i]->Render();
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
  remove_if(this->components.begin(), this->components.end(), [=](unique_ptr<Component> &cpt_alocado)
            { return cpt_recebido == cpt_alocado.get(); });
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
  Component *result_cpt = nullptr;

  for (int i = 0; i < (int)this->components.size(); i++){
    Component *cpt = this->components[i].get();
    if(cpt && cpt->Is(type)){
      result_cpt = cpt;
      break;
    }
  }
  
  return result_cpt;
}

void GameObject::NotifyCollision(GameObject &other) {
  for (int i = 0; i < (int)this->components.size();i++)
    this->components[i].get()->NotifyCollision(other);
}
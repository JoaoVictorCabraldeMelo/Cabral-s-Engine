
#include "../include/Component.hpp"
#include "../include/GameObject.hpp"

#include <algorithm>
#include <memory>

using namespace std;

GameObject::GameObject() : started(false), angleDeg(0.0), isDead(false)
{}

GameObject::~GameObject()
{
  components.clear();
}

void GameObject::Update(float dt)
{
  for (size_t i = 0; i < components.size(); i++)
    components[i]->Update(dt);
}

void GameObject::Render()
{
  for (size_t i = 0; i < components.size(); i++)
    components[i]->Render();
}

bool GameObject::IsDead() const
{
  return isDead;
}

void GameObject::RequestDelete()
{
  isDead = true;
}

void GameObject::AddComponent(Component *cpt)
{
  components.emplace_back(cpt);
  if (started)
    cpt->Start();
}

void GameObject::RemoveComponent(Component *cpt_recebido)
{
  remove_if(components.begin(), components.end(), [=](unique_ptr<Component> &cpt_alocado)
            { return cpt_recebido == cpt_alocado.get(); });
}

void GameObject::Start()
{
  for (const auto &component : components)
  {
    component->Start();
  }
  started = true;
}

Component *GameObject::GetComponent(const string& type) const
{
  Component *result_cpt = nullptr;

  for (size_t i = 0; i < components.size(); i++){
    Component *cpt = components[i].get();
    if(cpt && cpt->Is(type)){
      result_cpt = cpt;
      break;
    }
  }
  
  return result_cpt;
}

void GameObject::NotifyCollision(GameObject &other) {
  for (size_t i = 0; i < components.size();i++)
    components[i].get()->NotifyCollision(other);
}
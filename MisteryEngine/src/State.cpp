#include "../include/State.hpp"
#include "../include/InputManager.hpp"
#include "../include/Collider.hpp"
#include "../include/Collision.hpp"

#include <set>

using namespace std;

State::State() : popRequested(false), quitRequested(false), started(false) {}

State::~State() 
{
  objectArray.clear();
}

weak_ptr<GameObject> State::AddObject(GameObject *object) {
  shared_ptr<GameObject> shared_go(object);

  objectArray.push_back(shared_go);

  if (started)
    shared_go->Start();

  weak_ptr<GameObject> weak_go(shared_go);
  return weak_go;
}

weak_ptr<GameObject>  State::GetObject(GameObject *object) {

  for (size_t i = 0; i < objectArray.size(); i++)
  {
    if (objectArray[i].get() == object)
    {
      weak_ptr<GameObject> weak_go(objectArray[i]);
      return weak_go;
    }
  }

  return {};
}

bool State::PopRequested() const { return popRequested; }

bool State::QuitRequested() const { return quitRequested; }

void State::StartArray() {
  for (size_t i = 0; i < objectArray.size();++i)
    objectArray[i].get()->Start();
}

void State::UpdateArray(float dt) {

  /*Normal Update*/
  for (size_t i = 0; i < objectArray.size();++i)
    objectArray[i].get()->Update(dt);
  
  /*-------------*/

  /*Detecting Colision*/
  set<pair<GameObject *, GameObject *>> collisions;

  for (int i = 0; i < (int)this->objectArray.size(); i++)
  {
    for (int j = i; j < (int)this->objectArray.size(); j++)
    {
      if (i != j)
      {
        GameObject *go_i = this->objectArray[i].get();
        GameObject *go_j = this->objectArray[j].get();
        if (go_i->GetComponent("Collider") && go_j->GetComponent("Collider"))
          collisions.insert(make_pair(go_i, go_j));
      }
    }
  }

  for (auto &collision : collisions)
  {
    GameObject *first_box = collision.first;
    GameObject *second_box = collision.second;

    Collider *first_collider = static_cast<Collider *>(first_box->GetComponent("Collider"));
    Collider *second_collider = static_cast<Collider *>(second_box->GetComponent("Collider"));

    bool collided = Collision::IsColliding(first_collider->box, second_collider->box, first_box->angleDeg, second_box->angleDeg);

    if (collided)
    {
      first_box->NotifyCollision(*second_box);
      second_box->NotifyCollision(*first_box);
    }
  }
  /*---------------*/

  /*Removing Objects*/
  for (size_t i = 0; i < objectArray.size();++i){
    if (objectArray[i].get()->IsDead())
      RemoveObject(i);
  }
}

void State::RenderArray() {
  for (size_t i = 0; i < objectArray.size(); ++i)
    objectArray[i].get()->Render();
}

void State::RemoveObject(const int position) {
  
  objectArray.erase(objectArray.begin() + position);

}

weak_ptr<GameObject> State::FindObjectByName(const string& name)
{
  for (size_t i = 0; i < objectArray.size(); i++){
    if (objectArray[i].get()->name == name){
      weak_ptr<GameObject> weak_go(objectArray[i]);
      return weak_go;
    }
  }
  return {};
}
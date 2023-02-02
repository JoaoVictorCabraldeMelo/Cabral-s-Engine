#include "../include/State.hpp"
#include "../include/InputManager.hpp"

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
  for (size_t i = 0; i < objectArray.size();++i)
    objectArray[i].get()->Update(dt);

  for (size_t i = 0; i < objectArray.size();++i){
    if (objectArray[i].get()->IsDead())
      RemoveObject(i);
  }
}

void State::RenderArray() {
  for (size_t i = 0; i < objectArray.size(); ++i)
    objectArray[i].get()->Render();
  InputManager::GetInstance().Render();
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
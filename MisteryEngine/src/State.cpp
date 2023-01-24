#include "../include/State.hpp"

using namespace std;

State::State() : popRequested(false), quitRequested(false), started(false) {}

State::~State() {
  for (size_t i = 0; i < this->objectArray.size(); ++i) {
    this->objectArray[i].get()->RequestDelete();
  }
  this->objectArray.clear();
}

weak_ptr<GameObject> State::AddObject(GameObject *object) {
  shared_ptr<GameObject> shared_go(object);

  this->objectArray.push_back(shared_go);

  if (this->started)
    shared_go->Start();

  weak_ptr<GameObject> weak_go(shared_go);
  return weak_go;
}

weak_ptr<GameObject>  State::GetObject(GameObject *object) {

  for (size_t i = 0; i < this->objectArray.size(); i++)
  {
    if (this->objectArray[i].get() == object)
    {
      weak_ptr<GameObject> weak_go(this->objectArray[i]);
      return weak_go;
    }
  }

  return {};
}

bool State::PopRequested() { return this->popRequested; }

bool State::QuitRequested() { return this->quitRequested; }

void State::StartArray() {
  for (size_t i = 0; i < this->objectArray.size();++i)
    this->objectArray[i].get()->Start();
}

void State::UpdateArray(float dt) {
  for (size_t i = 0; i < this->objectArray.size();++i)
    this->objectArray[i].get()->Update(dt);
}

void State::RenderArray() {
  for (size_t i = 0; i < this->objectArray.size(); ++i)
    this->objectArray[i].get()->Render();
}
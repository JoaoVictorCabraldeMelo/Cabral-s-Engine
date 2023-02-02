#include "../include/Object.hpp"
#include "../include/Sprite.hpp"
#include "../include/Collider.hpp"

using namespace std;

Object::Object(GameObject &associated, const std::string& file) : Component(associated) 
{
  Sprite *object_sprite = new Sprite(associated, file);

  associated.box.w = object_sprite->GetWidth();

  associated.box.h = object_sprite->GetHeight();

  associated.AddComponent(object_sprite);

  associated.AddComponent(new Collider(associated));
}

Object::~Object(){}

void Object::Update(float dt) {
}

void Object::Render() {}

bool Object::Is(const std::string& type){
  if(type == "Object")
    return true;
  return false;
}

void Object::Start() {}

void Object::NotifyCollision(GameObject &other) {
  printf("Colidiu\n");
}
#include "../include/Object.hpp"
#include "../include/Sprite.hpp"
#include "../include/Collider.hpp"
#include "../include/Collision.hpp"

using namespace std;

Object::Object(GameObject &associated, const std::string& file, GameObject &mouse,  const Vec2& scale) 
: Component(associated), file(file), sprite(nullptr), mouse(mouse), scale(scale) 
{
  Sprite *object_sprite = new Sprite(associated, file);

  sprite = object_sprite;

  associated.box.w = object_sprite->GetWidth();

  associated.box.h = object_sprite->GetHeight();

  associated.AddComponent(object_sprite);

  associated.AddComponent(new Collider(associated));

  sprite->SetScale(scale.x, scale.y);
}

Object::~Object(){}

void Object::Update(float dt) {

  Collider *object_collider = static_cast<Collider *>(associated.GetComponent("Collider"));
  Collider *mouse_collider = static_cast<Collider *>(mouse.GetComponent("Collider"));

  bool is_colliding = Collision::IsColliding(object_collider->box, mouse_collider->box, associated.angleDeg, mouse.angleDeg);

  if (!is_colliding) {
    if (sprite) {
      associated.RemoveComponent(sprite);
      sprite = nullptr;
    }
  }
}

void Object::Render() {}

bool Object::Is(const std::string& type){
  if(type == "Object")
    return true;
  return false;
}

void Object::Start() {
  if (sprite) {
    associated.RemoveComponent(sprite);
    sprite = nullptr;
  } /*segfault protection*/
}

void Object::NotifyCollision(GameObject &other) {
  if (sprite == nullptr) {
    Sprite *object_sprite = new Sprite(associated, "assets/img/telefoneOutline.png");

    sprite = object_sprite;

    associated.AddComponent(object_sprite);
    // sprite->SetScale(3.7, 3.7);
  }
}
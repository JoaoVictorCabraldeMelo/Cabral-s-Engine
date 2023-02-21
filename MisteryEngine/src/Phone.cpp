#include "../include/Phone.hpp"
#include "../include/Collider.hpp"
#include "../include/Collision.hpp"

using namespace std;

Phone::Phone(GameObject& associated, const std::string& file, vector<string>& actions, GameObject& mouse, const Vec2& scale)
: Component(associated), file(file), sprite(nullptr), mouse(mouse), scale(scale)
{

  Sprite *phone_sprite = new Sprite(associated, file);

  sprite = phone_sprite;

  associated.box.w = phone_sprite->GetWidth();

  associated.box.h = phone_sprite->GetHeight();

  associated.AddComponent(phone_sprite);

  associated.AddComponent(new Collider(associated));
}

Phone::~Phone() {}

void Phone::Update(float dt) {
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

void Phone::Render() {}

void Phone::Start() {
  if (sprite)
  {
    associated.RemoveComponent(sprite);
    sprite = nullptr;
  } /*segfault protection*/
}

bool Phone::Is(const std::string& type){
  if (type == "Phone")
    return true;
  return false;
}

void Phone::NotifyCollision(GameObject &other) {
  if (sprite == nullptr)
  {
    Sprite *object_sprite = new Sprite(associated, "assets/img/phone.png");

    sprite = object_sprite;

    associated.AddComponent(object_sprite);

  }
}

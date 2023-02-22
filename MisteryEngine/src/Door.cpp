#include "../include/Door.hpp"
#include "../include/Sala.hpp"
#include "../include/Game.hpp"
#include "../include/Collider.hpp"
#include "../include/Collision.hpp"
#include "../include/Mouse.hpp"

using namespace std;

Door::Door(GameObject& associated, const std::string& file, vector<string>& actions, GameObject& mouse, const Vec2& scale)
: Component(associated), file(file), sprite(nullptr), mouse(mouse), isColliding(false) ,scale(scale)
{

  Sprite *door_sprite = new Sprite(associated, file);

  sprite = door_sprite;

  associated.box.w = door_sprite->GetWidth();

  associated.box.h = door_sprite->GetHeight();

  associated.AddComponent(door_sprite);

  associated.AddComponent(new Collider(associated));
}

Door::~Door() {}

void Door::Update(float dt) {
  Collider *object_collider = static_cast<Collider *>(associated.GetComponent("Collider"));
  Collider *mouse_collider = static_cast<Collider *>(mouse.GetComponent("Collider"));

  bool is_colliding = Collision::IsColliding(object_collider->box, mouse_collider->box, associated.angleDeg, mouse.angleDeg);


  if (!is_colliding) {
    if (sprite) {
      associated.RemoveComponent(sprite);
      sprite = nullptr;
      isColliding = false;
    }
  }
}

void Door::Render() {}

void Door::Start() {
  if (sprite)
  {
    associated.RemoveComponent(sprite);
    sprite = nullptr;
  } /*segfault protection*/
}

bool Door::Is(const std::string& type){
  if (type == "Door")
    return true;
  return false;
}

void Door::NotifyCollision(GameObject &other) {
  if (sprite == nullptr)
  {
    Sprite *object_sprite = new Sprite(associated, "assets/img/door.png");

    sprite = object_sprite;

    associated.AddComponent(object_sprite);

    Mouse *cpt = static_cast<Mouse *>(other.GetComponent("Mouse"));

    if (cpt)
      isColliding = true;
  }
}

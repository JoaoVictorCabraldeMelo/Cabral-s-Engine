#include "../include/Armario.hpp"
#include "../include/Collider.hpp"
#include "../include/Collision.hpp"
#include "../include/Quarto.hpp"

using namespace std;

Armario::Armario(GameObject &associated, const std::string &file, vector<string> &actions, GameObject &mouse, const Vec2 &scale)
    : Component(associated), file(file), sprite(nullptr), mouse(mouse), isColliding(false) , scale(scale)
{
  Sprite *wardrobe_sprite = new Sprite(associated, file);

  sprite = wardrobe_sprite;

  associated.box.w = wardrobe_sprite->GetWidth();

  associated.box.h = wardrobe_sprite->GetHeight();

  associated.AddComponent(wardrobe_sprite);

  associated.AddComponent(new Collider(associated));
}

Armario::~Armario() {}

void Armario::Update(float dt) {
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

void Armario::Render() {}

void Armario::Start() {
  if (sprite)
  {
    associated.RemoveComponent(sprite);
    sprite = nullptr;
  } /*segfault protection*/
}

bool Armario::Is(const std::string& type){
  if (type == "Armario")
    return true;
  return false;
}

void Armario::NotifyCollision(GameObject &other) {
  if (sprite == nullptr)
  {
    Sprite *object_sprite = new Sprite(associated, "assets/img/wardrobe.png");

    sprite = object_sprite;

    associated.AddComponent(object_sprite);

    isColliding = true;
  }
}

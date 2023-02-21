#include "../include/Soro.hpp"
#include "../include/Collider.hpp"
#include "../include/Collision.hpp"

using namespace std;

Soro::Soro(GameObject& associated, const std::string& file, vector<string>& actions, GameObject& mouse, const Vec2& scale)
: Component(associated), file(file), sprite(nullptr), mouse(mouse), scale(scale)
{

  Sprite *soro_sprite = new Sprite(associated, file);

  sprite = soro_sprite;

  associated.box.w = soro_sprite->GetWidth();

  associated.box.h = soro_sprite->GetHeight();

  associated.AddComponent(soro_sprite);

  associated.AddComponent(new Collider(associated));
}

Soro::~Soro() {}

void Soro::Update(float dt) {
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

void Soro::Render() {}

void Soro::Start() {
  if (sprite)
  {
    associated.RemoveComponent(sprite);
    sprite = nullptr;
  } /*segfault protection*/
}

bool Soro::Is(const std::string& type){
  if (type == "Soro")
    return true;
  return false;
}

void Soro::NotifyCollision(GameObject &other) {
  if (sprite == nullptr)
  {
    Sprite *object_sprite = new Sprite(associated, "assets/img/soro.png");

    sprite = object_sprite;

    associated.AddComponent(object_sprite);

  }
}

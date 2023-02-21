#include "../include/PortaSala.hpp"
#include "../include/Rua.hpp"
#include "../include/Game.hpp"
#include "../include/Collider.hpp"
#include "../include/Collision.hpp"

using namespace std;

PortaSala::PortaSala(GameObject& associated, const std::string& file, vector<string>& actions, GameObject& mouse, const Vec2& scale)
: Component(associated), file(file), sprite(nullptr), mouse(mouse), scale(scale)
{

  Sprite *tv_sprite = new Sprite(associated, file);

  sprite = tv_sprite;

  associated.box.w = tv_sprite->GetWidth();

  associated.box.h = tv_sprite->GetHeight();

  associated.AddComponent(tv_sprite);

  associated.AddComponent(new Collider(associated));
}

PortaSala::~PortaSala() {}

void PortaSala::Update(float dt) {
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

void PortaSala::Render() {}

void PortaSala::Start() {
  if (sprite)
  {
    associated.RemoveComponent(sprite);
    sprite = nullptr;
  } /*segfault protection*/
}

bool PortaSala::Is(const std::string& type){
  if (type == "PortaSala")
    return true;
  return false;
}

void PortaSala::NotifyCollision(GameObject &other) {
  if (sprite == nullptr)
  {
    Sprite *object_sprite = new Sprite(associated, "assets/img/porta_sala.png");

    sprite = object_sprite;

    associated.AddComponent(object_sprite);
    Rua *rua = new Rua();
    Game::GetInstance().Push(rua);

  }
}

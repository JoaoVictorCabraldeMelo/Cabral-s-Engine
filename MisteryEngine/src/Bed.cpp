#include "../include/Bed.hpp"
#include "../include/Collider.hpp"
#include "../include/Collision.hpp"
#include "../include/Mouse.hpp"

using namespace std;

Bed::Bed(GameObject& associated, const std::string& file, vector<string>& actions, GameObject& mouse, const Vec2& scale)
: Component(associated), file(file), sprite(nullptr), mouse(mouse), isColliding(false) ,scale(scale)
{

  Sprite *bed_sprite = new Sprite(associated, file);

  sprite = bed_sprite;

  associated.box.w = bed_sprite->GetWidth();

  associated.box.h = bed_sprite->GetHeight();

  associated.AddComponent(bed_sprite);

  associated.AddComponent(new Collider(associated));
}

Bed::~Bed() {}

void Bed::Update(float dt) {
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

void Bed::Render() {}

void Bed::Start() {
  if (sprite)
  {
    associated.RemoveComponent(sprite);
    sprite = nullptr;
  } /*segfault protection*/
}

bool Bed::Is(const std::string& type){
  if (type == "Bed")
    return true;
  return false;
}

void Bed::NotifyCollision(GameObject &other) {
  if (sprite == nullptr)
  {
    Sprite *object_sprite = new Sprite(associated, "assets/img/bed.png");

    sprite = object_sprite;

    associated.AddComponent(object_sprite);
    
    Mouse *cpt = static_cast<Mouse *>(other.GetComponent("Mouse"));

    if (cpt)
      isColliding = true;
  }
}

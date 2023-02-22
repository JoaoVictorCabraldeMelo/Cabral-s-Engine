#include "../include/Bed.hpp"
#include "../include/Collider.hpp"
#include "../include/Collision.hpp"
#include "../include/Mouse.hpp"
#include "../include/Quarto.hpp"

using namespace std;

Bed::Bed(GameObject& associated, const std::string& file, vector<string>& actions, GameObject& mouse, const Vec2& scale)
: Component(associated), file(file), actions(actions), sprite(nullptr), mouse(mouse), isColliding(false) ,scale(scale), chooser_sprite(nullptr), chooser_text(nullptr)
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
      if (chooser_sprite)
      {
        Quarto::chooser->RemoveComponent(chooser_sprite);
      }
      if (chooser_text)
      {
        Quarto::text->RemoveComponent(chooser_text);
      }
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

    if (cpt) {
      isColliding = true;

      Sprite *chooser_sprite = new Sprite(*Quarto::chooser, "assets/img/chooser.png");

      Quarto::chooser->AddComponent(chooser_sprite);

      Quarto::chooser->box.x = associated.box.x + 25;
      Quarto::chooser->box.y = associated.box.y - 100;

      this->chooser_sprite = chooser_sprite;

      Text *chooser_text = new Text(*Quarto::text, "assets/font/Mukta-Regular.ttf", 50, Text::TextStyle::SOLID, actions[0], {255, 255, 255, 255});
      Quarto::text->AddComponent(chooser_text);

      Quarto::text->box.x = associated.box.x + 50;
      Quarto::text->box.y = associated.box.y - 100;

      this->chooser_text = chooser_text;
    }
  }
}

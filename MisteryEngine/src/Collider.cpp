#include "../include/Collider.hpp"
#include "../include/Camera.hpp"

#ifdef DEBUG
#include "../include/Game.hpp"
extern const float PI;
#endif

using namespace std;

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated) {

  this->scale = scale;

  this->offset = offset;
}

void Collider::Update(float dt) {
  this->box = this->associated.box * this->scale;

  Vec2 center_box = this->associated.box.get_center();

  float angleRadians = degrees_to_radians(this->associated.angleDeg);
  this->offset.rotate(angleRadians);

  this->box.set_center(center_box);
}

void Collider::Render(){
#ifdef DEBUG

  Vec2 center(box.get_center());
  SDL_Point points[5];

  Vec2 point = (Vec2(this->box.x, this->box.y) - center).rotate(associated.angleDeg / (180 / PI)) + center - Camera::pos;
  points[0] = {(int)point.x, (int)point.y};
  points[4] = {(int)point.x, (int)point.y};

  point = (Vec2(this->box.x + this->box.w, this->box.y) - center).rotate(associated.angleDeg / (180 / PI)) + center - Camera::pos;
  points[1] = {(int)point.x, (int)point.y};

  point = (Vec2(this->box.x + this->box.w, this->box.y + this->box.h) - center).rotate(associated.angleDeg / (180 / PI)) + center - Camera::pos;
  points[2] = {(int)point.x, (int)point.y};

  point = (Vec2(this->box.x, this->box.y + this->box.h) - center).rotate(associated.angleDeg / (180 / PI)) + center - Camera::pos;
  points[3] = {(int)point.x, (int)point.y};

  SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
};

bool Collider::Is(string type) {
  if (type == "Collider")
    return true;
  return false;
}

void Collider::SetScale(Vec2 scale) {
  this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
  this->offset = offset;
}


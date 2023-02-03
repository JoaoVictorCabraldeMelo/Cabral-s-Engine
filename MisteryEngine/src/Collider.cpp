#include "../include/Collider.hpp"
#include "../include/Camera.hpp"

#ifdef DEBUG
#include "../include/Game.hpp"
#endif

using namespace std;

Collider::Collider(GameObject &associated, const Vec2& scale, const Vec2& offset) 
: Component(associated), scale(scale), offset(offset) {}

void Collider::Update(float dt) {
  box = associated.box * scale;

  float angleRadians = degrees_to_radians(associated.angleDeg);
  offset.rotate(angleRadians);

  box.x = associated.box.x;
  box.y = associated.box.y;
}

void Collider::Render(){
#ifdef DEBUG

  Vec2 center(box.get_center());
  SDL_Point points[5];

  Vec2 point = (Vec2(box.x, box.y) - center).rotate(associated.angleDeg / (180 / Vec2::PI)) + center - Camera::pos;
  points[0] = {(int)point.x, (int)point.y};
  points[4] = {(int)point.x, (int)point.y};

  point = (Vec2(box.x + box.w, box.y) - center).rotate(associated.angleDeg / (180 / Vec2::PI)) + center - Camera::pos;
  points[1] = {(int)point.x, (int)point.y};

  point = (Vec2(box.x + box.w, box.y + box.h) - center).rotate(associated.angleDeg / (180 / Vec2::PI)) + center - Camera::pos;
  points[2] = {(int)point.x, (int)point.y};

  point = (Vec2(box.x, box.y + box.h) - center).rotate(associated.angleDeg / (180 / Vec2::PI)) + center - Camera::pos;
  points[3] = {(int)point.x, (int)point.y};

  SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
};

bool Collider::Is(const string& type) {
  if (type == "Collider")
    return true;
  return false;
}

void Collider::SetScale(const Vec2& scale) {
  this->scale = scale;
}

void Collider::SetOffset(const Vec2& offset) {
  this->offset = offset;
}


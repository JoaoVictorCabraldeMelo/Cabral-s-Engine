#include "../include/Collider.hpp"

using namespace std;

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated) {

  this->scale = scale;

  this->offset = offset;
}

void Collider::Update(float dt) {
  this->box = this->associated.box * this->scale;

  pair<float, float> center_box = this->associated.box.get_center();
  Vec2 vec_center{center_box.first, center_box.second};

  float angleRadians = degrees_to_radians(this->associated.angleDeg);
  this->offset.rotate(angleRadians);

  vec_center = vec_center + this->offset;

  this->box.set_center(vec_center.x, vec_center.y);
}

void Collider::Render(){};

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


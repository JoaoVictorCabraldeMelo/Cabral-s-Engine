#include "../include/Bullet.hpp"
#include "../include/Sprite.hpp"
#include "../include/Component.hpp"


using namespace std;


Bullet::Bullet(GameObject &associated, float angle, float speed_x, float speed_y, int damage, float max_distance, string sprite) : Component(associated) {

  Sprite *bullet = new Sprite(associated, sprite, 3, .5F);

  bullet->SetScale(.75F, .75F);

  this->associated.angleDeg = angle;

  this->associated.AddComponent(bullet);

  this->speed.x = speed_x;

  this->speed.y = speed_y;

  this->damage = damage;

  this->distance_left = max_distance;

  this->associated.box.w = bullet->GetWidth();

  this->associated.box.h = bullet->GetHeight();

}

void Bullet::Update(float dt) {

  Vec2 current_position {this->associated.box.x, this->associated.box.y};

  float next_x = this->associated.box.x + this->speed.x * dt;
  float next_y = this->associated.box.y + this->speed.y * dt;

  float distance = current_position.distance(next_x, next_y);

  this->associated.box.x += this->speed.x * dt;

  this->associated.box.y += this->speed.y * dt;

  this->distance_left -= distance;

  if(this->distance_left <= 0) {
    this->associated.RequestDelete();
  }
}

void Bullet::Render() {

}

int Bullet::GetDamage() {
  return this->damage;
}

bool Bullet::Is(string type) {
  if (type == "Bullet")
    return true;
  return false;
}

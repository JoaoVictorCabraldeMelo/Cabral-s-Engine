#include "../include/Bullet.hpp"
#include "../include/Sprite.hpp"
#include "../include/Component.hpp"


using namespace std;


Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float max_distance, string sprite) : Component(associated) {

  Sprite *bullet = new Sprite(associated, sprite);

  this->associated.AddComponent(bullet);

  this->speed.x = speed;

  this->speed.y = speed;

  this->damage = damage;

  this->distance_left = max_distance;
}

void Bullet::Update(float dt) {

  this->associated.box.x = this->speed.x * dt;

  this->associated.box.y = this->speed.y * dt;

  this->distance_left -= this->speed.x * dt;

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

#include "../include/Bullet.hpp"
#include "../include/Sprite.hpp"
#include "../include/Component.hpp"
#include "../include/Collider.hpp"
#include "../include/PenguinBody.hpp"
#include "../include/PenguinCannon.hpp"
#include "../include/Alien.hpp"
#include "../include/Minion.hpp"


using namespace std;


Bullet::Bullet(GameObject &associated, float angle, float speed, bool targetsPlayer, int frames, int damage, float max_distance, string sprite) : Component(associated) {

  Sprite *bullet = new Sprite(associated, sprite, frames, .5F);

  Collider *bullet_collider = new Collider(associated);

  this->associated.angleDeg = angle;

  Vec2 line{max_distance, 0};

  float angle_rad = degrees_to_radians(angle);

  line.rotate(angle_rad);

  this->associated.AddComponent(bullet);
  this->associated.AddComponent(bullet_collider);

  this->speed = line * speed * .1F;

  this->damage = damage;

  this->distance_left = max_distance;

  this->targetsPlayer = targetsPlayer;

  this->associated.box.w = bullet->GetWidth();

  this->associated.box.h = bullet->GetHeight();

}

void Bullet::Update(float dt) {

  this->associated.box.x += this->speed.x * dt;

  this->associated.box.y += this->speed.y * dt;

  this->distance_left -= this->speed.magnitude() * dt;

  if(abs(this->distance_left) <= this->speed.magnitude() * dt) {
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

void Bullet::NotifyCollision(GameObject &other) {
  Alien *maybe_alien = static_cast<Alien *>(other.GetComponent("Alien"));
  Minion *maybe_minion = static_cast<Minion *>(other.GetComponent("Minion"));
  PenguinBody *maybe_pbody= static_cast<PenguinBody *>(other.GetComponent("PenguinBody"));

  if ((maybe_alien || maybe_minion) && !this->targetsPlayer)
    this->associated.RequestDelete();
  else if (maybe_pbody && this->targetsPlayer)
    this->associated.RequestDelete();

}
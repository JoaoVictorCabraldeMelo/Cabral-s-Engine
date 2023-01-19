#include "../include/Bullet.hpp"
#include "../include/Sprite.hpp"
#include "../include/Component.hpp"
#include "../include/Collider.hpp"
#include "../include/PenguinBody.hpp"
#include "../include/PenguinCannon.hpp"


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

  // Bullet *maybe_bullet = (Bullet *) other.GetComponent("Bullet");
  // PenguinBody *maybe_pbody = (PenguinBody *) other.GetComponent("PenguinBody");
  // PenguinCannon *maybe_pcannon = (PenguinCannon *)other.GetComponent("PenguinCannon");

  // bool collided_bullet = this->targetsPlayer && (maybe_pcannon || maybe_pbody);

  // if (!maybe_bullet && collided_bullet)
  //   other.RequestDelete();
}
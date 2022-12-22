#include "../include/Bullet.hpp"


using namespace std;


Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float max_distance, string sprite) : Component(associated) {

}

void Bullet::Update(float dt) {

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

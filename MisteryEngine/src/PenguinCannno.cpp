#include "../include/PenguinCannon.hpp"
#include "../include/Sprite.hpp"

using namespace std;

PenguinCannon::PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody)
  : Component(associated)
{
  Sprite *penguin_cannon_sprite = new Sprite(associated, "assets/img/cubngun.png");

  associated.AddComponent(penguin_cannon_sprite);

  this->pbody = penguinBody;

  this->angle = 0.0F;
};

void PenguinCannon::Update(float dt) {
  
}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(string type)
{
  if (type == "PenguinCannon")
    return true;
  return false;
}

void PenguinCannon::Shoot()
{
}

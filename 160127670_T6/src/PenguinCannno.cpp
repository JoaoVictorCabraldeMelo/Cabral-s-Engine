#include "../include/PenguinCannon.hpp"

using namespace std;

PenguinCannon::PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody)
    : Component(associated){};

void PenguinCannon::Update(float dt) {}

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

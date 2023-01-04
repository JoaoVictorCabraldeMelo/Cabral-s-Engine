#include "../include/PenguinBody.hpp"
#include "../include/Sprite.hpp"

using namespace std;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated){
  Sprite *penguin_body_sprite = new Sprite(associated, "assets/img/penguin.png");

  this->associated.AddComponent(penguin_body_sprite);

  this->angle = 0.0F;

  Vec2 speed{100, 100};

  this->speed = speed;

  this->linearSpeed = 0.0F;

  this->hp = 30;

};

void PenguinBody::Start(){};

PenguinBody::~PenguinBody(){};

void PenguinBody::Update(float dt){};

void PenguinBody::Render(){};

bool PenguinBody::Is(string type)
{
  if (type == "PenguinBody")
    return true;
  return false;
}
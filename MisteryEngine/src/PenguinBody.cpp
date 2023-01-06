#include "../include/PenguinBody.hpp"
#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
#include "../include/State.hpp"
#include "../include/PenguinCannon.hpp"
#include "../include/InputManager.hpp"

using namespace std;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated){
  Sprite *penguin_body_sprite = new Sprite(associated, "assets/img/penguin.png");

  this->associated.AddComponent(penguin_body_sprite);

  this->angle = 0.0F;

  Vec2 speed{100, 100};

  this->speed = speed;

  this->linearSpeed = 0.0F;

  this->hp = 30;

  this->player = this;
};

void PenguinBody::Start(){
  State &state = Game::GetInstance().GetState();

  GameObject *penguin_cannon_object = new GameObject();

  weak_ptr<GameObject> penguin_body = state.GetObjectPtr(&this->associated);

  PenguinCannon *penguin_cannon = new PenguinCannon(*penguin_cannon_object, penguin_body);

  penguin_cannon_object->AddComponent(penguin_cannon);

  this->pcannon = state.AddObject(penguin_cannon_object);
};

PenguinBody::~PenguinBody(){
  this->player = nullptr;
};

void PenguinBody::Update(float dt){
  InputManager &input = InputManager::GetInstance();

  float acceleration = 50.0F;

  bool w_pressed = input.KeyPress(W_KEY), s_pressed = input.KeyPress(S_KEY);

  if(w_pressed) {
    if(this->speed.x < 200 && this->speed.y < 200){
      this->linearSpeed += acceleration * dt;
    }
  }
  else if (s_pressed) {
    if(this->speed.x > - 200 && this->speed.y > - 200){
      this->linearSpeed -= acceleration * dt;
    }
  }

  this->associated.box.x += this->speed.x * dt;
  this->associated.box.y += this->speed.y * dt;

};

void PenguinBody::Render(){};

bool PenguinBody::Is(string type)
{
  if (type == "PenguinBody")
    return true;
  return false;
}
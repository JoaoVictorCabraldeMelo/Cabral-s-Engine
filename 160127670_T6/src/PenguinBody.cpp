#include "../include/PenguinBody.hpp"
#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
#include "../include/State.hpp"
#include "../include/PenguinCannon.hpp"
#include "../include/InputManager.hpp"

using namespace std;

extern const float DEG45;

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

  float speed_rotation = DEG45 * dt;

  bool w_pressed = input.KeyPress(W_KEY), s_pressed = input.KeyPress(S_KEY);
  bool a_pressed = input.KeyPress(A_KEY), d_pressed = input.KeyPress(D_KEY);

  if(w_pressed) {
    if(this->linearSpeed < 200){
      this->linearSpeed += acceleration * dt;
    }
  }
  else if (s_pressed) {
    if(this->linearSpeed > - 200){
      this->linearSpeed -= acceleration * dt;
    }
  }
  else if (a_pressed) {
    this->angle += speed_rotation;
  } else if (d_pressed) {
    this->angle -= speed_rotation;
  }

  this->associated.box.x += this->speed.x * this->linearSpeed * dt;
  this->associated.box.y += this->speed.y * this->linearSpeed * dt;



};

void PenguinBody::Render(){};

bool PenguinBody::Is(string type)
{
  if (type == "PenguinBody")
    return true;
  return false;
}
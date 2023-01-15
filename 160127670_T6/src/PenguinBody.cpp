#include "../include/PenguinBody.hpp"
#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
#include "../include/State.hpp"
#include "../include/PenguinCannon.hpp"
#include "../include/InputManager.hpp"

using namespace std;

extern const float DEG30;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated){
  Sprite *penguin_body_sprite = new Sprite(associated, "assets/img/penguin.png");

  this->associated.AddComponent(penguin_body_sprite);

  this->angle = 0.0F;

  Vec2 speed{10, 10};

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

  Vec2 position{5, 0};

  float acceleration = 5.0F;

  float speed_rotation = DEG30 * dt;

  bool w_pressed = input.isKeyDown(W_KEY), s_pressed = input.isKeyDown(S_KEY);
  bool a_pressed = input.isKeyDown(A_KEY), d_pressed = input.isKeyDown(D_KEY);

  if(w_pressed) {
    if (this->linearSpeed < 200)
    {
      this->linearSpeed += acceleration * dt;
    }
  }
  else if (s_pressed) {
    if(this->linearSpeed > - 200){
      this->linearSpeed -= acceleration * dt;
    }
  }
  
  if (a_pressed) {
    this->angle += speed_rotation;
  } else if (d_pressed) {
    this->angle -= speed_rotation;
  }

  this->associated.angleDeg = radians_to_degrees(this->angle);

  position.rotate(this->angle);

  this->associated.box.x += position.x;
  this->associated.box.y += position.y;

  this->associated.box.x += this->speed.x * this->linearSpeed * dt;
  this->associated.box.y += this->speed.y * this->linearSpeed * dt;


  if (hp <= 0){
    this->associated.RequestDelete();
    GameObject* penguin_cannon = this->pcannon.lock().get();
    penguin_cannon->RequestDelete();
  }
};

void PenguinBody::Render(){};

bool PenguinBody::Is(string type)
{
  if (type == "PenguinBody")
    return true;
  return false;
}
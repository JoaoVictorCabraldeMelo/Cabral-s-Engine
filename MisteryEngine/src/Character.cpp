#include "../include/Character.hpp"
#include "../include/Sprite.hpp"
#include "../include/InputManager.hpp"
#include "../include/Game.hpp"
#include "../include/Camera.hpp"

using namespace std;

Character::Character(GameObject &associated, string sprite, int frame_count) : Component(associated) {

  Sprite *character_sprite = new Sprite(associated, sprite, frame_count, .2F);

  this->associated.AddComponent(character_sprite);

  Vec2 speed{100, 0};

  this->speed = speed;

  this->associated.box.w = character_sprite->GetWidth();

  this->associated.box.h = character_sprite->GetHeight();
}


void Character::Start() {
  Sprite *character_sprite = static_cast<Sprite *> (this->associated.GetComponent("Image"));

  character_sprite->SetFlip(Sprite::Flip::HORIZONTAL);  
  this->sprite_direction = Direction::RIGHT;

  character_sprite->SetScale(.4F, 1.0F);

  this->associated.box.y = 360 * Game::GetInstance().GetScreenScale().y;
  this->associated.box.x = 20 * Game::GetInstance().GetScreenScale().x;
}

void Character::Update(float dt) {

  Camera::Update(dt);

  InputManager &input = InputManager::GetInstance();

  int mouse_x = input.GetMouseX();

  bool left_mouse_button = input.MousePress(LEFT_MOUSE_BUTTON);

  Sprite *sprite_character = static_cast<Sprite*>(this->associated.GetComponent("Image"));

  if(left_mouse_button) 
    this->destinations.push({(float) mouse_x, this->associated.box.y});

  if (!this->destinations.empty()) {
    Vec2 destination = this->destinations.front();

    if (destination.x > this->associated.box.x && this->sprite_direction == Direction::LEFT)
    {
      sprite_character->SetFlip(Sprite::Flip::HORIZONTAL);
      this->sprite_direction = Direction::RIGHT;
    }
    else if (destination.x < this->associated.box.x && this->sprite_direction == Direction::RIGHT)
    {
      sprite_character->SetFlip(Sprite::Flip::NONE);
      this->sprite_direction = Direction::LEFT;
    }

    Vec2 current_position{this->associated.box.x, this->associated.box.y};

    destination.x -= this->associated.box.w;

    Vec2 result_position = destination - current_position;

    result_position.normalise();

    float distance = current_position.distance_x(destination);

    if (distance <= 10.0)
    {
      this->associated.box.x = destination.x;
      this->destinations.pop();
    }
    else
      this->associated.box.x += result_position.x * this->speed.x * dt;
  } 
  else 
    sprite_character->SetFrame(0);
  
}

void Character::Render(){}

bool Character::Is(string type) {
  if (type == "Character") 
    return true;
  return false;
}

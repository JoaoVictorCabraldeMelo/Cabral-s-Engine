#include "../include/Character.hpp"
#include "../include/Sprite.hpp"
#include "../include/InputManager.hpp"
#include "../include/Game.hpp"
#include "../include/Camera.hpp"

#include <cstdio>

using namespace std;

Character::Character(GameObject &associated, string sprite, int frame_count) : Component(associated), speed({100, 0}) {

  Sprite *character_sprite = new Sprite(associated, sprite, frame_count, .2F);

  associated.AddComponent(character_sprite);

  associated.box.w = character_sprite->GetWidth();

  associated.box.h = character_sprite->GetHeight();
}

void Character::Start() {
  Sprite *character_sprite = static_cast<Sprite*> (associated.GetComponent("Image"));

  character_sprite->SetFlip(Sprite::Flip::HORIZONTAL);  
  sprite_direction = Direction::RIGHT;

  associated.box.y = 420 * Game::GetInstance().GetScreenScale().y;
  associated.box.x = 80 * Game::GetInstance().GetScreenScale().x;
}

void Character::Update(float dt) {

  Camera::Update(dt);

  InputManager &input = InputManager::GetInstance();

  int mouse_x = input.GetMouseX();

  bool left_mouse_button = input.MousePress(LEFT_MOUSE_BUTTON);

  Sprite *sprite_character = static_cast<Sprite*>(associated.GetComponent("Image"));

  if(left_mouse_button) 
    destinations.push({(float) (mouse_x - Camera::pos.x), associated.box.y});

  if (!destinations.empty()) {
    Vec2 destination = destinations.front();

    Vec2 face { associated.box.x, associated.box.y};


    if (destination.x > face.x && sprite_direction == Direction::LEFT)
    {
      sprite_character->SetFlip(Sprite::Flip::HORIZONTAL);
      sprite_direction = Direction::RIGHT;
    }
    else if (destination.x < face.x && sprite_direction == Direction::RIGHT)
    {
      sprite_character->SetFlip(Sprite::Flip::NONE);
      sprite_direction = Direction::LEFT;
    }

    Vec2 current_position{associated.box.x + associated.box.w, associated.box.y};

    Vec2 result_position = Vec2::Sub(destination, current_position).normalise();

    float distance = current_position.distance(destination);


    if (distance <= 20.0)
    {
      destinations.pop();
    }
    else
      associated.box.x += result_position.x * this->speed.x * dt;
  } 
  else 
    sprite_character->SetFrame(0);
  
}

void Character::Render(){}

bool Character::Is(const string& type) {
  if (type == "Character") 
    return true;
  return false;
}

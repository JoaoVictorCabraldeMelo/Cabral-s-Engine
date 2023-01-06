#include "../include/Character.hpp"
#include "../include/Sprite.hpp"
#include "../include/InputManager.hpp"

using namespace std;

Character::Character(GameObject &associated, string sprite, int frame_count) : Component(associated) {

  Sprite *character_sprite = new Sprite(associated, sprite, frame_count, .4F);

  this->associated.AddComponent(character_sprite);

  Vec2 speed{100, 100};

  this->speed = speed;

  this->associated.box.w = character_sprite->GetWidth();

  this->associated.box.h = character_sprite->GetHeight();
}

Character::Action::Action(ActionType action, float x, float y) {
  this->type = action;

  this->pos.x = x;
  this->pos.y = y;
}

void Character::Start() {
  Sprite *character_sprite = (Sprite *) this->associated.GetComponent("Image");

  character_sprite->SetScale(.8F, .8F);
}

void Character::Update(float dt) {

  InputManager &input = InputManager::GetInstance();

  int mouse_x = input.GetMouseX(), mouse_y = input.GetMouseY();

  bool right_click = input.MousePress(RIGHT_MOUSE_BUTTON);

  if(right_click) {
    Character::Action new_action = Character::Action(Action::MOVE, mouse_x, mouse_y);
    this->taskQueue.push(new_action);
  }

  if(!this->taskQueue.empty()) {
    Vec2 current_position{this->associated.box.x, this->associated.box.y}, final_position;

    Action last_action = this->taskQueue.front();

    final_position = last_action.pos;

    Vec2 result_position;

    result_position.x = final_position.x - current_position.x;
    result_position.y = final_position.y - current_position.y;

    Vec2 base{0, 0};

    float length_vector = result_position.magnitude(base);

    Vec2 normalized_vector{result_position.x / length_vector, result_position.y / length_vector};

    float distance = final_position.distance(current_position.x, current_position.y);

    if(distance <= 10.0) {

      this->associated.box.x = final_position.x;
      this->associated.box.y = final_position.y;
      this->taskQueue.pop();
    } else if (last_action.type == Action::MOVE) {
      this->associated.box.x += normalized_vector.x * this->speed.x * dt;
      this->associated.box.y += normalized_vector.y * this->speed.y * dt;
    }
  }
}

void Character::Render(){}

bool Character::Is(string type) {
  if (type == "Character") 
    return true;
  return false;
}

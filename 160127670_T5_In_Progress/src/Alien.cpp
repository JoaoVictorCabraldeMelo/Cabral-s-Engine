#include "../include/Alien.hpp"
#include "../include/Sprite.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"

using namespace std;

#include <iostream>
#include <fstream>

Alien::Alien(GameObject &associated, int nMinions) : Component(associated)
{

  Component *alien_sprite = new Sprite(associated, "assets/img/alien.png");

  this->associated.AddComponent(alien_sprite);
}

Alien::~Alien()
{
  while (!this->minionArray.empty())
    this->minionArray.pop_back();
}

void Alien::Start()
{
}

Alien::Action::Action(ActionType type, float x, float y)
{
  this->type = type;
  this->pos.x = x;
  this->pos.y = y;
}

void Alien::Update(float dt)
{

  bool left_click = InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON);
  bool right_click = InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON);

  if (left_click || right_click)
  {

    int mouse_x = InputManager::GetInstance().GetMouseX();
    int mouse_y = InputManager::GetInstance().GetMouseY();

    Camera::pos.x += mouse_x;
    Camera::pos.y += mouse_y;

    if (left_click)
    {
      Alien::Action new_action = Alien::Action::Action(Action::SHOOT, mouse_x, mouse_y);
      this->taskAction.push(new_action);
    }
    else
    {
      Alien::Action new_action = Alien::Action::Action(Action::MOVE, mouse_x, mouse_y);
      this->taskAction.push(new_action);
    }

    if (!this->taskAction.empty)
    {
      auto action = this->taskAction.front();
      if (action.type == Action::MOVE)
      {
        this->speed = Vec2(action.pos.x, action.pos.y);
      }
    }
  }
}
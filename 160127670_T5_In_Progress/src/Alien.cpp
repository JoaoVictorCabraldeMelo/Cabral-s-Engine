#include "../include/Alien.hpp"
#include "../include/Sprite.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/Vec2.hpp"
#include <iostream>
#include <fstream>

using namespace std;

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
  cout << "Delta :" << dt << endl;

  bool left_click = InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON);
  bool right_click = InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON);

  int mouse_x = InputManager::GetInstance().GetMouseX();
  int mouse_y = InputManager::GetInstance().GetMouseY();

  if (left_click || right_click)
  {

    Camera::pos.x = mouse_x;
    Camera::pos.y = mouse_y;
  
    if (left_click)
    {
      Alien::Action new_action = Alien::Action(Action::SHOOT, mouse_x, mouse_y);
      this->taskQueue.push(new_action);
    }
    else
    {
      Alien::Action new_action = Alien::Action(Action::MOVE, mouse_x, mouse_y);
      this->taskQueue.push(new_action);
    }
  }

  if (!this->taskQueue.empty())
  {

    Alien::Action pendent_action = this->taskQueue.front();

    float alien_x = this->associated.box.x;
    float alien_y = this->associated.box.y;

    this->speed.x = (pendent_action.pos.x - alien_x) / dt;
    this->speed.y = (pendent_action.pos.y - alien_y) / dt;

    cout << "Velocidade eixo X e eixo Y: " << this->speed.x << " " << this->speed.y << endl;

    float distance = pendent_action.pos.distance(alien_x, alien_y);

    // cout << "Distância: " << distance << endl;
    if (distance < 100.00)
    {
      this->associated.box.x = pendent_action.pos.x;
      this->associated.box.y = pendent_action.pos.y;
      this->taskQueue.pop();
    }
    else if (pendent_action.type == Action::MOVE)
    {
      // this->associated.box.x += this->speed.x * dt;
      // this->associated.box.y += this->speed.y * dt;
    }
    else if (pendent_action.type == Action::SHOOT)
    {
      this->taskQueue.pop();
    }
  }

  if (this->hp == 0)
    this->associated.RequestDelete();
}

void Alien::Render()
{
}

bool Alien::Is(string type)
{
  if (type == "Alien")
    return true;
  return false;
}
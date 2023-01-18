#include "../include/Alien.hpp"
#include "../include/Sprite.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/Vec2.hpp"
#include "../include/Minion.hpp"
#include "../include/Game.hpp"

#include <iostream>
#include <fstream>

using namespace std;

Alien::Alien(GameObject &associated, int nMinions) : Component(associated), speed(SPEEDX, SPEEDY)
{

  Sprite *alien_sprite = new Sprite(associated, "assets/img/alien.png");

  this->associated.AddComponent(alien_sprite);

  this->nMinions = nMinions;

  this->hp = 50;

  this->associated.box.w = alien_sprite->GetWidth();
  this->associated.box.h = alien_sprite->GetHeight();
}

Alien::Action::Action(ActionType type, float x, float y)
{
  this->type = type;
  this->pos.x = x;
  this->pos.y = y;
}

Alien::~Alien()
{
  this->minionArray.clear();
}

void Alien::Start()
{

  Game &instance = Game::GetInstance();

  State &game_state = instance.GetState();

  weak_ptr<GameObject> alien_go = game_state.GetObjectPtr(&this->associated);

  for (int i = 0; i <= this->nMinions; i++)
  {
    GameObject *minion_go = new GameObject();

    Component *minion = new Minion(*minion_go, alien_go, i * ((2 * PI) / this->nMinions));

    minion_go->AddComponent(minion);

    weak_ptr<GameObject> weak_go = game_state.AddObject(minion_go);

    this->minionArray.push_back(weak_go);
  }
}

void Alien::Update(float dt)
{
  // cout << "Delta :" << dt << endl;

  bool left_click = InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON);

  bool right_click = InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON);

  int mouse_x = InputManager::GetInstance().GetMouseX();

  int mouse_y = InputManager::GetInstance().GetMouseY();

  float angle_clockwise_degrees = -(DEG30 * 180 / PI) * dt;

  this->associated.angleDeg += angle_clockwise_degrees;

  if (left_click || right_click)
  {
    int camera_x = Camera::pos.x;
    int camera_y = Camera::pos.y;

    if (left_click)
    {
      Alien::Action new_action = Alien::Action(Action::SHOOT, mouse_x + camera_x, mouse_y + camera_y);
      this->taskQueue.push(new_action);
    }
    else
    {
      Alien::Action new_action = Alien::Action(Action::MOVE, mouse_x + camera_x, mouse_y + camera_y);
      this->taskQueue.push(new_action);
    }
  }

  if (!this->taskQueue.empty())
  {

    Alien::Action pendent_action = this->taskQueue.front();

    Vec2 alien_center = this->associated.box.get_center();

    Vec2 final_position{pendent_action.pos.x, pendent_action.pos.y};
    Vec2 result_position;

    result_position = final_position - alien_center;

    result_position.normalise();

    float distance = pendent_action.pos.distance(alien_center);

    if (distance <= 10.0)
    {
      this->associated.box.set_center(pendent_action.pos);
      this->taskQueue.pop();
    }
    else if (pendent_action.type == Action::MOVE)
    {
      Vec2 new_position = result_position * this->speed * dt;

      this->associated.box.x += new_position.x;
      this->associated.box.y += new_position.y;
    }
    else if (pendent_action.type == Action::SHOOT)
    {
      float min_distance = MAXFLOAT;

      int minion_index = 0;

      for (int i = 0; i < this->nMinions; i++)
      {
        Rect minion_box = this->minionArray[i].lock()->box;

        float current_distance = minion_box.distance(pendent_action.pos);

        if (current_distance < min_distance)
        {
          min_distance = current_distance;
          minion_index = i;
        }
      }

      GameObject *minion_ptr = this->minionArray[minion_index].lock().get();

      Minion *minion_cpt = (Minion *)minion_ptr->GetComponent("Minion");

      minion_cpt->Shoot(pendent_action.pos);

      this->taskQueue.pop();
    }
  }

  if (this->hp <= 0)
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
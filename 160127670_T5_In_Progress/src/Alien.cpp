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

    Minion *minion = new Minion(*minion_go, alien_go, i*((2*PI) / this->nMinions));

    minion_go->AddComponent(minion);

    game_state.AddObject(minion_go);

    shared_ptr<Minion> shared_minion(minion);

    weak_ptr<Minion> weak_minion(shared_minion);

    this->minionArray.push_back(weak_minion);
  }
}

void Alien::Update(float dt)
{
  // cout << "Delta :" << dt << endl;

  bool left_click = InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON);

  bool right_click = InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON);

  int mouse_x = InputManager::GetInstance().GetMouseX();

  int mouse_y = InputManager::GetInstance().GetMouseY();

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

    // cout << "Posicao pendente eixo X e eixo Y: " << pendent_action.pos.x << " " << pendent_action.pos.y << endl;

    float alien_x = this->associated.box.x;
    float alien_y = this->associated.box.y;

    Vec2 inital_position{alien_x, alien_y};
    Vec2 final_position{pendent_action.pos.x, pendent_action.pos.y};
    Vec2 result_position;

    result_position.x = final_position.x - inital_position.x;
    result_position.y = final_position.y - inital_position.y;

    Vec2 base{0, 0};

    float length_vector = result_position.magnitude(base);

    Vec2 normalized_vector{result_position.x / length_vector, result_position.y / length_vector};

    float distance = pendent_action.pos.distance(alien_x, alien_y);

    // cout << "Distância: " << distance << endl;
    if (distance <= 10.0)
    {
      this->associated.box.x = pendent_action.pos.x;
      this->associated.box.y = pendent_action.pos.y;
      this->taskQueue.pop();
    }
    else if (pendent_action.type == Action::MOVE)
    {
      this->associated.box.x += normalized_vector.x * this->speed.x * dt;
      this->associated.box.y += normalized_vector.y * this->speed.y * dt;
    }
    else if (pendent_action.type == Action::SHOOT)
    {
      int minion = rand() % this->nMinions;

      Minion *minion_ptr = this->minionArray[minion].lock().get();

      minion_ptr->Shoot(pendent_action.pos);

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
#include "../include/Face.hpp"
#include "../include/Music.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "../include/SDL_include.hpp"

#include <chrono>
#include <thread>

using namespace std;

Face::Face(GameObject &associated) : Component(associated)
{
  this->hitpoints = 30;
}

Face::~Face()
{
}

void Face::Damage(int damage)
{
  if (this->hitpoints <= 0)
  {

    Music *Sound = static_cast<Music *>(this->associated.GetComponent("Sound"));

    if (Sound != nullptr)
    {
      Sound->Play();
    }

    this_thread::sleep_for(chrono::nanoseconds(10));

    this_thread::sleep_until(chrono::system_clock::now() + chrono::seconds(1));

    this->associated.RequestDelete();
  }
  else
  {
    this->hitpoints -= damage;
  }
}

void Face::Update(float dt)
{

  if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) || InputManager::GetInstance().MousePress(SDL_BUTTON_RIGHT))
  {
    bool is_in = this->associated.box.is_point_in((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY());
    if (is_in)
    {
      this->Damage(rand() % 10 + 10);
    }
  }
}

void Face::Render()
{
}

bool Face::Is(const string type)
{
  if (type == "Face")
    return true;
  else
    return false;
}